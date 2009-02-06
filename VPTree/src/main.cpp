#include <iostream>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

#include "siftset.h"
#include "desc.h"

using namespace std;




int main()
{
	SiftSet siftset("../Samples/database.data", "../Samples/sifts_files.data");


	// -------------- Utilisation de la classe SiftSet ----------------------
	//Pour boucler sur tous les SIFTs
	for (Desc sift = siftset.begin(); !sift.coeffs.empty(); sift = siftset.next())
	{
		//Do stuff with sift
	}

	//Pour accéder au SIFT par son numéro
	Desc sift = siftset(11);

	//Pour accéder à tous les SIFTs de l'image numéro...
	std::vector<Desc> res = siftset.get_sifts_in_image(2);
	cout << "Il y a " << res.size() << " sifts dans l'image " << 2 << endl;
	// ----------------------------------------------------------------------


	//Pour faire le K-Means sur l'espace des SIFTs
	const int K = 5;								//Nombre de classes = K
	Desc *centers = new Desc[K];
	siftset.do_k_means(K, centers);

	display(centers[0].coeffs);
	cout << endl;



	delete [] centers;
	system("pause");
	return 0;
}

