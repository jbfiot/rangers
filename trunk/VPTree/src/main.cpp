#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "feature.h"
#include "bof_db.h"
#include "feature_db.h"
#include "time.h"

using namespace std;

#include "tools.h"


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
    fdb.fill_with_random(15, 200);

    cout << endl << "============================================================"
		 << endl << "   Etape 2: K-Means  "
		 << endl << "============================================================" <<endl;
	int K = 5;
	std::vector<Vector> centers;
	fdb.do_k_means(K, centers);

    cout << endl << "============================================================"
		 << endl << "   Etape3:Initialisation de la base de données de BOFs   "
		 << endl << "============================================================" <<endl;
	Bof_db bof_db(centers);



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
		std::vector<Bof> all_regions_in_image = get_all_regions_subsets( res );

		//Pour l'instant, on ne met qu'un BOF contenant les 2 premiers SIFTs de l'image
		/**	std::vector<Feature> feats;					**/
		/**	feats.push_back(res[0]);					**/
		/**	feats.push_back(res[1]);					**/
		/**	std::vector<Bof> all_regions_in_image;		**/
		/**	all_regions_in_image.push_back(Bof(feats));	**/

		//Ajout de la BOF à  la database
		for (int j=0; j<all_regions_in_image.size(); ++j)
		{
			Bof bof = all_regions_in_image[j];
			bof_db.add_bof(bof);
		}

	}


    cout << endl << "==============================================================="
		     << endl << "   Etape5: Construction de l'arbre et sauvegarde dans la bdd"
		     << endl << "===============================================================" <<endl;
	bof_db.build_tree();


	system("pause");
	return 0;
}
