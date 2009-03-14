#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "time.h"
#include "tools.h"

#include "feature_db.h"
#include "bof_db.h"
#include "bof_db_region.h"

using namespace std;


//#define USE_REGION


int main()
{
	srand ( time(NULL) );

	cout << endl << "============================================================"
		<< endl << "   Etape 0: Instanciation de la BDD de Features"
		<< endl << "============================================================" <<endl;
	Feature_db fdb;

	cout << endl << "============================================================"
		<< endl << "   Etape 1: Remplissage de la base de données de Features"
		<< endl << "============================================================" <<endl;
	//fdb.fill_with_random(15, 100);

	cout << endl << "============================================================"
		<< endl << "   Etape 2: K-Means  "
		<< endl << "============================================================" <<endl;
	int K = 5;
	std::vector<Vector> centers;
	Vector sigmas;
	fdb.do_k_means(K, centers, sigmas,true);



	cout << endl << "============================================================"
		<< endl << "   Etape3:Initialisation de la base de données de BOFs   "
		<< endl << "============================================================" <<endl;
#ifdef USE_REGION
	Bof_db_Region bof_db(&fdb, centers.size());
#else
	Bof_db bof_db(centers, sigmas);
#endif


	cout << endl << "========================================================================"
		<< endl << "   Etape4: Extraction des régions des images et insertion dans la base"
		<< endl << "========================================================================" <<endl;
	for (int i=1; i<fdb.get_nbimages()+1; ++i)
	{
		cout << "Image number " << i << endl;

		//Tous les SIFTs dans l'image i
		std::vector<Feature> res;
		fdb.get_all_features_in_image(i, res);

		// Calcul des régions
#ifdef USE_REGION
		std::vector<Bof_Region> all_regions_in_image;

		//Pour l'instant, on ne met qu'un BOF_Region contenant deux sifts au PIF
		// (des indexs de 2 features entre 1 et 1000)
		std::vector<int> feature_indexes;
		feature_indexes.push_back(rand()%1000);
		feature_indexes.push_back(rand()%1000);

		Bof_Region region(feature_indexes, &fdb, &centers);
		all_regions_in_image.push_back( region );

#else
		std::vector<Bof> all_regions_in_image;
		int nb_pixels = 200;
		get_all_regions_subsets( res, all_regions_in_image, nb_pixels );
		cout << all_regions_in_image.size() << " bofs will be added to the database..." << endl;
#endif


		//Ajout de la BOF à  la database
		for (int j=0; j<all_regions_in_image.size(); ++j)
			bof_db.add_bof( all_regions_in_image[j] );

		cout << "Done." << endl << endl;

	}


	cout << endl << "==============================================================="
		<< endl << "   Etape5: Construction de l'arbre et sauvegarde dans la bdd"
		<< endl << "===============================================================" <<endl;
	bof_db.build_tree();


	cout << endl << endl << "==============================================================="
		<< endl << "   Etape6: Recherche dans l'arbre"
		<< endl << "===============================================================" <<endl;
	Vector bof;
	double mu, son1, son2;
	bof_db.get_bof_number(101, bof, mu, son1, son2);

	bof_db.find_nearest_leaf(bof);

	system("pause");
	return 0;
}
