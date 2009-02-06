#include <iostream>
#include <assert.h>


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
	// ----------------------------------------------------------------------



	int index = 3;
	std::vector<Desc> res = siftset.get_sifts_in_image(index);
	cout << "Il y a " << res.size() << " sifts dans l'image " << index << endl;


	const int K = 5;		//Nombre de classes

	cout << siftset.getnbsift() << endl;

	assert(K<SAMPLE_LENGTH_FOR_K_MEANS && SAMPLE_LENGTH_FOR_K_MEANS<siftset.getnbsift());

	Desc *centers = new Desc[K];
	siftset.do_k_means(K, centers);

	display(centers[0].coeffs);
	cout << endl;



	delete [] centers;
	system("pause");
	return 0;
}

