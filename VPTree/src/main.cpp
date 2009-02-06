#include <iostream>

#include "siftset.h"

#include <assert.h>

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"


using namespace std;


template <typename T>
void display(T sift)
{
	for (int i=0; i<sift.size();++i)
	{
		cout << sift[i] << " ";
	}
	cout << endl;
}

void display(std::vector<std::string> &sift)
{
	for (int i=0; i<sift.size(); ++i)
	{
		cout << sift[i] << endl;
	}
}



int main()
{
	SiftSet siftset("Samples\\database.data", "Samples\\sifts_files.data");


	// -------------- Utilisation de la classe SiftSet ----------------------
	//Pour boucler sur tous les SIFTs
	for (std::vector<double> sift = siftset.begin(); !sift.empty(); sift = siftset.next())
	{
		//Do stuff with sift
	}

	//Pour accéder au SIFT par son numéro
	std::vector<double> sift = siftset(11);
	// ----------------------------------------------------------------------


	const int K = 5;		//Nombre de classes

	cout << siftset.getnbsift() << endl;

	assert(K<SAMPLE_LENGTH_FOR_K_MEANS && SAMPLE_LENGTH_FOR_K_MEANS<siftset.getnbsift());

	std::vector<double> *centers = new std::vector<double>[K];
	siftset.do_k_means(K, centers);

	cout << endl;
	display(centers[0]);
	cout << endl;
	display(centers[1]);
	cout << endl;



	delete [] centers;
	system("pause");
	return 0;
}

