#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
 using namespace std;
#include "CImg.h"
 using namespace cimg_library;
#include "fonction_sift.h"
typedef  CImg<float> IMG;
#include "class_descripteur.h"
#include <vector>
using namespace std;
void main () 
{
	// Charger l image
	char filename[]="concorde.jpg";
	//Parametre par defaut du sift
	int octave=-1;
	int level=5;
	int o_min=-1;
	double threshold=0; 
	//Image
	IMG img= IMG (filename);
	//Creer le tableau de points
	tableau_descripteur R_Keypoints;
	//Effectuer le sift
	R_Keypoints = effectuer_sift (img, octave ,level, o_min,threshold);
	//afficher les resultats
	//afficher_image ( img_results, filename,500);
	//Taille du tableau de descripteurs
	cout << R_Keypoints.size() <<endl;
	//Recuperer un descripteur
	rangers_descripteur toto = R_Keypoints[4];
	//obtenir l orientation
	cout << toto.rangers_getorientation() << endl ; 
	// obtenir le descripteur
	vl_sift_pix * tab = toto.rangers_getdescripteur();
	for (int i=0; i<128 ; i++ ) 
	{	cout << *tab << endl;
		tab++;
	}
	// Obtenir les coordonnees du key point
	VlSiftKeypoint K = toto.rangers_getkeypoint();
	cout << K.x << " " << K.y << endl;
	//Afficher les resultats
	IMG img_results = image_resultats(img,R_Keypoints);
	cout << K.o << endl ;
	//afficher les resultats
	afficher_image ( img_results, filename,500);

}

