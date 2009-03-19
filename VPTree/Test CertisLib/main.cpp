#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "time.h"
#include "tools.h"

#include "feature_db.h"
#include "bof_db.h"
#include "bof_db_region.h"

#include "pic_db.h"

using namespace std;

//#define USE_REGION



/**
 ** calcul des regions : une région est formée d'un ou plusieurs carres de taille nb_pixels
 **/

void get_all_regions_subsets( const vector<Feature>& res, vector<Bof_Region>& all_regions_in_image, int nb_pixels,
							 Feature_db *fdb, std::vector<Vector> *k_centers)
{
	int maxX=0, maxY=0;
	int i=0, j=0, k=0, u=0, v=0, w=0;
	int itX=0, itY=0;
	vector<Feature> feats;

	for (i=0; i<res.size(); i++)
	{
		if (maxX<res[i].position[0])
			maxX=res[i].position[0];
		if (maxY<res[i].position[1])
			maxY=res[i].position[1];
	}

	vector< vector<int> > tab(maxX+1, vector<int> (maxY+1,0));

	for (i=0; i<res.size(); i++)
	{
		tab[res[i].position[0]][res[i].position[1]]=i+1;
	}

	//calcul de tous les carres possibles
	i=0;
	while (i<=maxX)
	{
		itY=0;
		j=0;
		while (j<=maxY)
		{
			for (i=nb_pixels*itX; i<nb_pixels*(itX+1);i++)
			{
				for (j=nb_pixels*itY; j<nb_pixels*(itY+1); j++)
				{
					if (i<=maxX && j<=maxY && tab[i][j])
						feats.push_back(res[tab[i][j]-1]);
				}
			}
			itY++;
			if (!feats.empty())
				all_regions_in_image.push_back(Bof_Region());
				all_regions_in_image.back().init_Bof_Region(feats, fdb, k_centers);
			feats.clear();
		}
		itX++;
	}

	cout<<"tous les carres faits"<<endl;



	// calcul de tous les rectangles possibles verticaux
	for (i=0; i<itX; i++)
	{
		for (u=0; u<itY; u++)
		{
			for (j=i*itY+u; j<(i+1)*itY; j++)
			{
				for (k=0; k<all_regions_in_image[j].features.size(); k++)
					feats.push_back(all_regions_in_image[j].features[k]);
				if (j>(i*itY)+u)
					all_regions_in_image.push_back(Bof_Region());
				all_regions_in_image.back().init_Bof_Region(feats, fdb, k_centers);
			}
			feats.clear();
		}
	}

	cout<<"tous les retangles verticaux faits"<<endl;

	// calcul de tous les rectangles possibles horizontaux
	for (j=0; j<itY; j++)
	{
		for (u=0; u<itX; u++)
		{
			for (i=0; i<itX-u; i++)
			{
				for (k=0; k<all_regions_in_image[j+(i+u)*itX].features.size(); k++)
					feats.push_back(all_regions_in_image[j+(i+u)*itX].features[k]);
				if (i>0)
					all_regions_in_image.push_back(Bof_Region());
					all_regions_in_image.back().init_Bof_Region(feats, fdb, k_centers);
			}
			feats.clear();
		}
	}

	cout<<"tous les rectangles horizontaux faits"<<endl;

	//calcul de tous les rectangles possibles horizontaux+verticaux
	for (i=0; i<itX; i++)
	{
		for (u=0; u<itY; u++)
		{
			for (j=i*itX+u+1; j<(i+1)*itX; j++)
			{
				for (v=1; v<itX-i; v++)
				{
					for (w=i*itX+u; w<j+1; w++)
					{
						if (v==1)
							for (k=0; k<all_regions_in_image[w].features.size(); k++)
								feats.push_back(all_regions_in_image[w].features[k]);
						for (k=0; k<all_regions_in_image[w+v*itX].features.size(); k++)
							feats.push_back(all_regions_in_image[w+v*itX].features[k]);
					}
					all_regions_in_image.push_back(Bof_Region());
					all_regions_in_image.back().init_Bof_Region(feats, fdb, k_centers);
				}
				feats.clear();
			}
		}
	}

	cout<<"rectangles horizontaux+verticaux"<<endl;

}






int main()
{
	srand ( time(NULL) );

	//Pic_db pdb("./Images");

	//Remplissage de la base de données de chemins
	//pdb.fill_db();
	//unsigned int nb_images = pdb.get_nbimages();
	//std::vector<std::string> filenames;
	//pdb.get_all_image_paths(filenames);

	cout << endl << "============================================================"
		<< endl << "   Etape 0: Instanciation de la BDD de Features"
		<< endl << "============================================================" <<endl;
	Feature_db fdb;

	cout << endl << "============================================================"
		<< endl << "   Etape 1: Remplissage de la base de données de Features"
		<< endl << "============================================================" <<endl;
	//fdb.fill(filenames, nb_images);




	cout << endl << "============================================================"
		<< endl << "   Etape 2: K-Means  "
		<< endl << "============================================================" <<endl;
	int K = 10;
	std::vector<Vector> centers;
	Vector sigmas;
	fdb.do_k_means(K, centers, sigmas);



	cout << endl << "============================================================"
		<< endl << "   Etape3:Initialisation de la base de données de BOFs   "
		<< endl << "============================================================" <<endl;
#ifdef USE_REGION
	Bof_db_Region bof_db(&fdb, centers.size());
#else
	Bof_db bof_db(centers, sigmas);
#endif

/*

	cout << endl << "========================================================================"
		<< endl << "   Etape4: Extraction des régions des images et insertion dans la base"
		<< endl << "========================================================================" <<endl;
	bof_db.erase();
	for (int i=1; i<fdb.get_nbimages()+1; ++i)
	{
		cout << "Image number " << i << endl;

		if (i==17) {
                cout << "screwed";
		}

		//Tous les SIFTs dans l'image i
		std::vector<Feature> res;
		fdb.get_all_features_in_image(i, res);
		int nb_pixels = 300;

		// Calcul des régions
#ifdef USE_REGION
		std::vector<Bof_Region> all_regions_in_image;

		get_all_regions_subsets(res, all_regions_in_image, nb_pixels, &fdb, &centers);

#else
		std::vector<Bof> all_regions_in_image;
		get_all_regions_subsets( res, all_regions_in_image, nb_pixels, i);
#endif

		cout << all_regions_in_image.size() << " bofs will be added to the database..." << endl;

		//Ajout de la BOF à  la database
		for (int j=0; j<all_regions_in_image.size(); ++j)
			bof_db.add_bof( all_regions_in_image[j] );

		cout << "Done." << endl << endl;

	}



	cout << endl << "==============================================================="
		<< endl << "   Etape5: Construction de l'arbre et sauvegarde dans la bdd"
		<< endl << "===============================================================" <<endl;
	bof_db.build_tree();

*/

	cout << endl << endl << "==============================================================="
		<< endl << "   Etape6: Recherche dans l'arbre"
		<< endl << "===============================================================" <<endl;
#ifdef USE_REGION
	Bof_Region bof;
#else
	Vector bof;
#endif

	double dummy_mu, dummy_son1, dummy_son2;
	bof_db.get_bof_number(12, bof, dummy_mu, dummy_son1, dummy_son2);

	//Vector lol;
	//process_sifts_in_image("AHAH.jpg", lol);


	bof_db.find_nearest_leaf(bof);



	system("pause");
	return 0;
}
