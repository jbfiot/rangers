#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "siftset.h"
#include "feature.h"
#include "bof_db.h"
#include "feature_db.h"

using namespace std;




int main()
{
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

	// ----------------------------------------------------------------------
*/


    cout << endl << "==================================="
		 << endl << "   Etape 0: Remplissage al�atoire de la BDD de sifts  "
		 << endl << "===================================" <<endl;

    Feature_db fdb;
    //fdb.fill_with_random(100);
	cout << fdb.get_nbfeatures() << endl;


    cout << endl << "==================================="
		 << endl << "   Etape 1: Appliquer l'algorithme de K-Means  "
		 << endl << "===================================" <<endl;

	int K = 5;
	std::vector<Vector> centers;
	fdb.do_k_means(K, centers);

	cout << centers[0] << endl;


	Vector vec;
	fdb.get_feature_number(1, vec);

	system("pause");
	return 0;

 //   cout << endl << "==================================="
	//<< endl << "  Etape1: Instancier la base de donnees de SIFTs   "
	//<< endl << "===================================" <<endl;
	//SiftSet sift_set("../Samples/database.data", "../Samples/sifts_files.data");



	//// Etape2: Faire le K-Means dans l'espace des SIFTs
	//int K = 5;
	//std::vector<Vector> centers;
	//siftset.do_k_means(K, centers);				//display(centers[0].coeffs);

	//// Etape3: initialisation de la base de donnÃ©es de BOFs
	//Bof_db bof_db(centers);//, "localhost", "root", "");



	////Etape4: Extraire les rÃ©gions dans chaque image et les insÃ©rer dans la base
	//for (int i=0; i<siftset.getnbimages(); ++i)
	//{
	//	//Tous les SIFTs dans l'image i
	//	std::vector<Feature> res = siftset.get_sifts_in_image(i);

	//	// !! FONCTION A IMPLEMENTER !!
	//	//std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );

	//	//Pour l'instant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
	//	/**/	std::vector<Feature> feats;					/**/
	//	/**/	feats.push_back(res[0]);					/**/
	//	/**/	feats.push_back(res[1]);					/**/
	//	/**/	std::vector<Bof> all_regions_in_image;		/**/
	//	/**/	all_regions_in_image.push_back(Bof(feats));	/**/

	//	//Ajout de la BOF Ã  la database
	//	for (int j=0; j<all_regions_in_image.size(); ++j)
	//	{
	//		Bof bof = all_regions_in_image[j];
	//		bof_db.add_bof(bof);
	//	}

	//}


	//	//std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );

	//	//Pour linstant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
	//	/**/	std::vector<Feature> feats;					/**/
	//	/**/	feats.push_back(sift_set(12));					/**/
	//	/**/	feats.push_back(sift_set(2));					/**/
	//	/**/	std::vector<Bof> all_regions_in_image;		/**/
	//	/**/	all_regions_in_image.push_back(Bof(feats));	/**/



	//	//Ajout de la BOF à la database
	//	bof_db.add_bof(all_regions_in_image[0]);






	//// Etape5: Construire l'arbre et le sauver dans la base de donnÃ©es
	//// !! FONCTION A IMPLEMENTER !!
	////bof_db.build_tree();


	//system("pause");
	//return 0;
}

