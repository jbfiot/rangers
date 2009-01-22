#include <iostream>
#include "siftset.h"

//Visual Leak Detector
//#include "vld.h"
//#include "vldapi.h"

using namespace std;


void display(int *sift)
{
	for (int i=0; i<128;++i)
	{
		cout << sift[i] << " ";
	}
	cout << endl;
}

void display(std::vector<std::string> &sift)
{
	cout << sift.size(); 
	for (int i=0; i<sift.size(); ++i)
	{
		cout << sift[i] << endl;
	}
}


int main()
{
	SiftSet siftset("Samples\\database.data", "Samples\\sifts_files.data");

	//Utilisation de la classe SiftSet
	for (int *sift = siftset.begin(); sift != 0; sift = siftset.next())
	{
		//Do stuff with sift
		delete sift;
	}

	cout << "----------------------TESTS--------------------" << endl;
	int *sift_1 = siftset.begin();
	delete sift_1;
	cout << "[0] " << sift_1[0] << endl;

	int i=0;
	for (int *sift = siftset.begin(); sift != 0; sift = siftset.next())
	{
		cout << "[" << i << "] " << sift[0] << endl;
		delete sift;
		++i;
	}
	cout << "-----------------------------------------------" << endl;



	system("pause");
	return 0;
}

