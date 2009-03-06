extern "C"
{
#include "sift.h"
	
}

#include <iostream>
using namespace std;
#include <fstream>
#include <string>

#include "CImg.h"
 using namespace cimg_library;
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
int load_image (CImg <T> &img, char * filename)
{
	
	
	cout << "------------------------------Chargement ------------------------" <<endl;
	cout<< "Entrez le nom de l'image a charger: " << endl;
	cin >> filename;
	img= CImg <T> (filename);
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
		*pix_val/=(depth*255);
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



//effectuer le sift

template <class T>
void effectuer_sift (const CImg <T> &img, CImg <T> &img_results, int &octave , int &level, int &o_min )
{
	//parametre de l image
	int width=img.width;
	int height= img.height;
	int color = 1;
	rgb2gray(img,img_results);
	cout << "-----------------------------------------------------------------" <<endl;
	cout << "Taille de l image:" << endl;
	cout << "width: " <<width <<endl;
	cout << "height: " << height<< endl;
	//// Convertir l image en en vl sift pix
	cout << "-----------------------------------------------------------------" <<endl;
	cout << "Convertir l image en en vl sift pix" << endl;
	vl_sift_pix const * pixels=Cimg2vl_sift_pix(img);
	//create a vl sift
	cout << "-----------------------------------------------------------------" << endl;
	cout<< "create a new vl sift" << endl;
	VlSiftFilt* f;
	f=  vl_sift_new(width,height,octave,level,o_min);	
	//process first octave
	//ouveture du fichier de stockage
	ofstream fichier("test.txt", ios::out | ios::trunc);
	if (!fichier)
	{
		cout<< "impossible d'ouvrir le fichier test.txt \n";
	
	}
	else
	{
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
					float keypoints_x = Keypoints->x;
					float keypoints_y = Keypoints->y;
					float keypoints_octave = Keypoints->sigma;
					fichier << i << " " << j+1 << " " << " " << keypoints_x << " " << keypoints_y << " " <<  angles[k] ;
					vl_sift_calc_keypoint_descriptor(f,descriptor,Keypoints,angles[k]);	
					vl_sift_pix  * descr = descriptor;
					for (int l = 0; l < 128; l++)
					{
						fichier << " " << *descr  ;
						descr++;
					}
					fichier << endl;
					
					img_results.draw_circle ( keypoints_x, keypoints_y, 3*keypoints_octave, &color,1,0);
	
				}
				Keypoints++;
			}
			cout << "-----------------------------------------------------------------" << endl;
			cout<< "Calcul des Orientations des Keypoints de la " << i << "eme octave"<< endl;
		}
		cout << "------------------------------------------------------------------------" << endl;
		cout << "Suppression du filtre" <<endl;
		vl_sift_delete(f);
		fichier.close();
	}
};


//recuperer les keypoints

