#pragma once

#ifndef _FONCTION_SIFT
#define _FONCTION_SIFT
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include "CImg.h"
 using namespace cimg_library;
#include "class_descripteur.h"



template <class T>
tableau_descripteur effectuer_sift (const CImg <T> &img, int &octave , int &level, int &o_min, double &threshold )
{
	tableau_descripteur _tableau_descripteur;
	//parametre de l image
	int width=img.width;
	int height= img.height;
	//convertir l image en vl sift pix
	vl_sift_pix const * pixels=Cimg2vl_sift_pix(img);
	//creer le filtre
	VlSiftFilt* f;
	f=  vl_sift_new(width,height,octave,level,o_min);
	// Regler le Threshold du detecteur
	double t1 =  vl_sift_get_peak_thresh (f);
	cout << t1 <<endl;
	vl_sift_set_peak_thresh	(f,threshold);
	for (int i=1;i<=f->O;i++)
	{
		if (i==1)
		{
			cout << "-----------------------------------------------------------------" << endl;
			cout<< "Processing de la premiere octave" << endl;
			int vlfirstoctave = vl_sift_process_first_octave(f,pixels);
			if (vlfirstoctave==VL_ERR_EOF) { break;}
		}
		else
		{
			cout << "-----------------------------------------------------------------" << endl;
			cout << "Processing de la "<< i << "eme octave" <<  endl;
			int vlsiftnextoctave= vl_sift_process_next_octave  (f)  ;
			if (vlsiftnextoctave==VL_ERR_EOF) { break;}
		}
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Detection" << endl;
		vl_sift_detect(f);
		//initialisation du pointeur sur la liste
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Obtention des Keypoints " << endl;
		VlSiftKeypoint const * Keypoints = vl_sift_get_keypoints( f) ;
		//obtention du nombre de Keypoints
		int nkeypoints = vl_sift_get_nkeypoints ( f);
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Nombre de Keypoints " << nkeypoints << endl ;
		for (int j=0;j<nkeypoints;j++)
		{
			
			double angles[4];
			int nkeypointorientation = vl_sift_calc_keypoint_orientations(f,angles,Keypoints);
			//cout << "Nombre d orientation du " << j+1 <<  "eme Key point " << nkeypointorientation << endl;
			//boucle sur les orientations	
			vl_sift_pix descriptor[128];

			for (int k=0;k<nkeypointorientation;k++)
			{
				
				vl_sift_calc_keypoint_descriptor(f,descriptor,Keypoints,angles[k]);	
				rangers_descripteur temp(angles[k],descriptor,*Keypoints);
				
				_tableau_descripteur.push_back(temp);
			}
			Keypoints++;
		}
	}
	return _tableau_descripteur;
};

typedef vector<rangers_descripteur> tableau_descripteur;

template <class T>
CImg<T> image_resultats (const CImg<T> &img,tableau_descripteur _tableau_descripteur)
{
	//creer une nouvelle image
	CImg<T> img_results =img;
	//creer un iterateur pour balayer le tableau de descripteur
	tableau_descripteur::const_iterator it;
	//afficher les resultats
	int color[3] = {255,0,0};
	unsigned int pattern = 10;
	for (it=_tableau_descripteur.begin(); it<_tableau_descripteur.end(); it++)
	{
		rangers_descripteur temp = *it;
		VlSiftKeypoint K = temp.rangers_getkeypoint();
		img_results.draw_circle(K.x,K.y,3*K.sigma,color,1.0,pattern);
	}
	return img_results;

};
//Menu 

 int menu () 
 {
	
	cout << "-------------------------------SIFT Menu ------------------------" <<endl;
	cout << "Choisissez l une des options suivantes " << endl;
	cout << "1 - Charger une Image " << endl;
	cout << "2 - Afficher l image chargee " << endl;
	cout << "3 - Regler les parametres du sift" << endl;
	cout << "4 - SIFT " << endl;
	cout << "5 - Afficher l image resultat" <<endl ;
	cout << endl;
	cout << "0 - Quitter " << endl << endl;
	cout << "choix : " ;
	int output;
	cin >> output;
	cout << endl;
	return output;
 };



//Chargement de l image en couleur (channel =3) ou en noir et blanc (1)
	
template <class T>
int load_image (CImg <T> &img,CImg <T> &img_results, char * filename)
{
	
	
	cout << "------------------------------Chargement ------------------------" <<endl;
	cout<< "Entrez le nom de l'image a charger: " << endl;
	cin >> filename;
	img= CImg <T> (filename);
	img_results= CImg <T> (filename);
	if (img.is_empty())
	{
		cout<< "Impossible de charger l'image  " << endl;
		return 5;
	}
	else
	{
		cout << "Image Chargee " << endl ;
		return 0;
	}
};


//Afficher l image

template<class T>
void afficher_image ( const CImg <T> & image, const char * filename,int size)
{
	
	
	char file_name[500];
	
	for (int i=0;i<size;i++)
	{
		file_name[i]=*filename;
		filename++;
	}
	CImgDisplay main_disp(image,file_name);
	//Attente d une intruction - fermeture de l image
	cout << "------------------------------Affichage -------------------------" <<endl;
	cout<< "Selectionner la fenetre de l image et la fermer pour continuer" << endl;
	while (!main_disp.is_closed) {
		main_disp.wait();
	}
};



//Parametre du sift

void sift_parametres (int & octave, int & level, int & o_min) 
{
	cout << "-------------------------Parametres du Sift ---------------------" <<endl;
	cout << "Parametres actuels" << endl;
	cout << "octave: " << octave <<  endl;
	cout << "level: " <<  level << endl;
	cout << "o_min: " <<  o_min << endl;
	cout << "Voulez vous les modifier? [y]/[n]" << endl;
	char r;
	cin >> r ;
	if (r=='y')
	{
		cout << "octave = " ; 
		cin >> octave;
		cout << "level = " ; 
		cin >> level;
		cout << "o_min = " ; 
		cin >> o_min;
		cout << "Modifications effectuees" <<endl;
	}
	else
	{
		cout << "Parametres inchanges " <<endl ;
	}
};

//convertir l image couleur en niveaux de gris entre 0 et 255

template<class T>
void rgb2gray (const CImg <T> & img, CImg <T> & img_gray)
{
	img_gray = CImg <T> ( img.width , img.height);
	CImg <T> :: const_iterator it;
	CImg <T> :: iterator itg;
	it=img.begin();
	
	itg=img_gray.begin();
	int depth = img.depth;
	while (itg!=img_gray.end())
	{
		*itg=0;
		for (int j=0 ; j< depth; j++)
		{
			*itg+=*it;
			it++;
		}
		*itg/=(depth);
		itg++;
	}				
};

// Conversion CImg image vers Vl sift Pix

template<class T>
vl_sift_pix* Cimg2vl_sift_pix( const CImg<T> &img )
{
	int height     = img.height;
	int width      = img.width;
	int depth	= img.depth;
	CImg < T>::const_iterator it = img.begin();
	
    int pixelN= height*width;
	vl_sift_pix* pix = new vl_sift_pix[ pixelN ];
    vl_sift_pix* pix_val = pix;
        
    for( int pos = 0; pos < pixelN; pos++ )
    {
		*pix_val=0;
		for (int color = 0 ; color < depth ; color ++ ) 
		{
			*pix_val += (vl_sift_pix)*it;
			
			it++;
		}
		*pix_val/=(depth);
		pix_val++;
    }
    return pix;
};



//conversion vl sift pix vers Cimg Image

template  <class T>
void  vlsiftpix2CImg (const vl_sift_pix * pix,  int width , int height ,CImg <T> &img)
{
	img = CImg <T> ( width,height);
	CImg <T>::iterator it = img.begin();
	
	while (it!=img.end())
	{
		*it=*pix;
		pix++;
		it++;
	}
	
};

#endif