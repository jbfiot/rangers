#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "siftset.h"
#include "feature.h"
#include "bof_db.h"
#include "feature_db.h"
#include "time.h"

using namespace std;




int main()
{
	srand ( time(NULL) );

    /*
	//TESTS

	// -------------- Utilisation de la classe SiftSet ----------------------
	SiftSet siftset("../Samples/database.data", "../Samples/sifts_files.data");
	
	//Pour boucler sur tous les SIFTs
	for (Feature sift = siftset.begin(); !sift.coeffs.empty(); sift = siftset.next())
	{
		//Do stuff with sift
	}

	//Pour accÃ©der au SIFT par son numÃ©ro
	Feature sift = siftset(11);

	//Pour accÃ©der Ã  tous les SIFTs de l'image numÃ©ro...
	std::vector<Feature> res = siftset.get_sifts_in_image(2);
	cout << "Il y a " << res.size() << " sifts dans l'image " << 2 << endl;




	Bof_db();

	Vector vec;
	fdb.get_feature_number(1, vec);

	std::vector<Vector> res;
	fdb.get_all_features_in_image(5, res);

	// ----------------------------------------------------------------------
*/


    cout << endl << "==================================="
		 << endl << "   Etape 1: Remplissage al�atoire de la BDD de sifts  "
		 << endl << "===================================" <<endl;
    Feature_db fdb;
    fdb.fill_with_random(10, 20);
	
	cout << fdb.get_nbfeatures() << endl;
	cout << fdb.get_nbimages() << endl;


    cout << endl << "==================================="
		 << endl << "   Etape 2: Appliquer l'algorithme des K-Means  "
		 << endl << "===================================" <<endl;
	int K = 5;
	std::vector<Vector> centers;
	fdb.do_k_means(K, centers);

    cout << endl << "==================================="
		 << endl << "   Etape3: initialisation de la base de donn�es de BOFs   "
		 << endl << "===================================" <<endl;
	Bof_db bof_db(centers);


    cout << endl << "==================================="
		 << endl << "   Etape4: Extraire les r�gions dans chaque image et les ins�rer dans la base   "
		 << endl << "===================================" <<endl;
	for (int i=1; i<fdb.get_nbimages()+1; ++i)
	{
		cout << "Image number " << i << endl;

		//Tous les SIFTs dans l'image i
		std::vector<Feature> res;
		fdb.get_all_features_in_image(i, res);

		// !! FONCTION A IMPLEMENTER !!
		//std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );

		//Pour l'instant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
		/**/	std::vector<Feature> feats;					/**/
		/**/	feats.push_back(res[0]);					/**/
		/**/	feats.push_back(res[1]);					/**/
		/**/	std::vector<Bof> all_regions_in_image;		/**/
		/**/	all_regions_in_image.push_back(Bof(feats));	/**/

		//Ajout de la BOF � la database
		for (int j=0; j<all_regions_in_image.size(); ++j)
		{
			Bof bof = all_regions_in_image[j];
			bof_db.add_bof(bof);
		}

	}



	// Etape5: Construire l'arbre et le sauver dans la base de donnÃ©es
	// !! FONCTION A IMPLEMENTER !!
	//bof_db.build_tree();


	system("pause");
	return 0;
}

