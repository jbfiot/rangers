
#include <iostream>
 using namespace std;
#include "CImg.h"
 using namespace cimg_library;
#include "fonction.h"

typedef  CImg<float> IMG;

void main () 
{
	//Variables
	int choix ;
	//Parametre par defaut du sift
	int octave=5;
	int level=5;
	int o_min=-1;
	
	int buffer_size = 500;
	char filename [500];
	// Image
	IMG img;
	IMG img_results;

	// 
	choix = menu ();
	
	while (choix!=0)
	{
		
		if (choix == 1)//charger l image
		{
			load_image(img,filename);
			cout<< *filename << endl;
		}
		else if (choix == 2)//afficher l image
		{
			afficher_image(img,filename,buffer_size);
		}
		else if (choix == 3)//Regler les parametres du sift
		{
			sift_parametres(octave,level,o_min);
		}
		else if (choix == 4) // perform sift
		{
			effectuer_sift(img,img_results,octave,level,o_min);
		}
		else if (choix == 5) // Image Results
		{
			afficher_image(img_results,filename,buffer_size);
		}
		choix = menu ();
	}
	cout << "A bientot!"<< endl ;
}




