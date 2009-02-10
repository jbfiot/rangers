#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "siftset.h"
#include "feature.h"
#include "bof_db.h"

using namespace std;




int main()
{
	SiftSet siftset("../Samples/database.data", "../Samples/sifts_files.data");

    /*
	//TESTS

	// -------------- Utilisation de la classe SiftSet ----------------------
	//Pour boucler sur tous les SIFTs
	for (Feature sift = siftset.begin(); !sift.coeffs.empty(); sift = siftset.next())
	{
		//Do stuff with sift
	}

	//Pour accéder au SIFT par son numéro
	Feature sift = siftset(11);

	//Pour accéder à tous les SIFTs de l'image numéro...
	std::vector<Feature> res = siftset.get_sifts_in_image(2);
	cout << "Il y a " << res.size() << " sifts dans l'image " << 2 << endl;


	cout << endl << "==================================="
		 << endl << "   Utilisation de la base Bof_db   "
		 << endl << "===================================" <<endl;

	Bof_db();

	// ----------------------------------------------------------------------
*/



	// Etape1: Instancier la base de données de SIFTs
	SiftSet sift_set("../Samples/database.data", "../Samples/sifts_files.data");

	// Etape2: Faire le K-Means dans l'espace des SIFTs
	int K = 5;
	std::vector<Feature> centers = siftset.do_k_means(K);				//display(centers[0].coeffs);

	// Etape3: initialisation de la base de données de BOFs
	Bof_db bof_db(centers);//, "localhost", "root", "");

	// Etape4: Extraire les régions dans chaque image et les insérer dans la base
//	for (int i=0; i<siftset.getnbimages(); ++i)
//	{
//		//Tous les SIFTs dans l'image i
//		std::vector<Feature> res = siftset.get_sifts_in_image(i);
//
//		// !! FONCTION A IMPLEMENTER !!
//		//std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );
//
//		//Pour linstant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
//		/**/	std::vector<Feature> feats;					/**/
//		/**/	feats.push_back(res[0]);					/**/
//		/**/	feats.push_back(res[1]);					/**/
//		/**/	std::vector<Bof> all_regions_in_image;		/**/
//		/**/	all_regions_in_image.push_back(Bof(feats));	/**/
//
//		//Ajout de la BOF à la database
//		for (int j=0; j<all_regions_in_image.size(); ++j)
//			bof_db.add_bof(all_regions_in_image[j]);
//
//	}


		//std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );

		//Pour linstant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
		/**/	std::vector<Feature> feats;					/**/
		/**/	feats.push_back(sift_set(12));					/**/
		/**/	feats.push_back(sift_set(2));					/**/
		/**/	std::vector<Bof> all_regions_in_image;		/**/
		/**/	all_regions_in_image.push_back(Bof(feats));	/**/



		//Ajout de la BOF � la database
		bof_db.add_bof(all_regions_in_image[0]);






	// Etape5: Construire l'arbre et le sauver dans la base de données
	// !! FONCTION A IMPLEMENTER !!
	//bof_db.build_tree();


	system("pause");
	return 0;
}

