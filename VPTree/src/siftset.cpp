#include <iostream>
#include <fstream>
#include "siftset.h"

#include <string>
#include <vector>

using namespace std;



int *SiftSet::operator ()(double index)
{
	return (this)->get_descriptor(index);
}

/**
 *	Constructeur => prend un fichier de base de donn�es et le fichier o� il y a le nom de tous les fichiers
 **/
SiftSet::SiftSet(char *name_base, char *name_sifts)
{
	files_names.clear();

	memcpy(name_database, name_base, sizeof(name_database));
	memcpy(name_sifts_files, name_sifts, sizeof(name_sifts_files));

	current_sift_index = 0;

	archive_files();
}

/**
 *	Met tous les noms des fichiers .SIFT dans un vecteur
 **/
void SiftSet::archive_files()
{
	ifstream fichier_database(name_sifts_files, ios::in);  // on ouvre le fichier en lecture

    if(!fichier_database)  // si l'ouverture a r�ussi
    {       
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		return;
    }

	std::string ligne; 
 
	while(getline(fichier_database,ligne)) 
	{ 
		files_names.push_back(ligne); 
	}
}


/**
 *	Initialise l'it�rateur
 **/
int *SiftSet::begin()
{
	if (fichier_sift.is_open())
	{
		fichier_sift.close();
		fichier_sift.clear();
	}

	std::string sift_file_name = files_names[0];
	memcpy(current_file, sift_file_name.c_str(), sizeof(current_file));

	//Ouverture du fichier sift
	fichier_sift.open(current_file, ios::in);

    if(!fichier_sift)  // si l'ouverture n'a pas r�ussi
    {       
		cerr << "Impossible d'ouvrir le fichier sift!" << endl;
		return NULL;
    }

	//On zappe la premi�re ligne
	std::string ligne;
	getline(fichier_sift, ligne);

	//R�cup�ration ds coordonn�es du SIFT
	int *sift = new int[128];
	int center_x, center_y;

	fichier_sift >> center_x >> center_y;
	
	for (int i=0; i<128; ++i)
		fichier_sift >> sift[i];

	//fichier_sift.close();

	current_sift_index = 1;
	index_file = 1;

	return sift;
}


/**
 *	Renvoie le SIFT suivant (apr�s initialisation de l'it�rateur)
 **/
int *SiftSet::next()
{
	//On continue � lire le fichier pr�c�dent
	//std::string line;

	
	if (fichier_sift.eof())
	{
		if (index_file == files_names.size())
			return NULL;

		std::string sift_file_name = files_names[index_file];
		memcpy(current_file, sift_file_name.c_str(), sizeof(current_file));

		//Ouverture du fichier sift
		fichier_sift.close();
		fichier_sift.clear();

		fichier_sift.open(current_file, ios::in);

		if(!fichier_sift.is_open())  // si l'ouverture n'a pas r�ussi
		{       
			cerr << endl << "Impossible d'ouvrir le fichier sift!" << endl;
			return NULL;
		}

		//On zappe la premi�re ligne
		std::string ligne;
		getline(fichier_sift, ligne);

		index_file++;
	}


	//R�cup�ration ds coordonn�es du SIFT
	int *sift = new int[128];
	int center_x, center_y;

	fichier_sift >> center_x >> center_y;
	
	for (int i=0; i<128; ++i)
		fichier_sift >> sift[i];

	current_sift_index ++;

	return sift;
}




/**
 *	R�cup�re les coordonn�es du SIFT num�ro index
 **/
int *SiftSet::get_descriptor(double index) const
{
	//Ouverture du fichier database
	ifstream fichier_database(name_database, ios::in);
    if(!fichier_database)  // si l'ouverture a r�ussi
    {       
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		return NULL;
    }
	std::string ligne;
	int index_ligne;


	//R�cup�ration du fichier et de l'offset o� se trouve le sift voulu
	for (int line=0; line<index; ++line)
		getline(fichier_database,ligne);

	fichier_database >> ligne >> index_ligne;
	fichier_database.close();


	//Ouverture du fichier sift
	ifstream fichier_sift(ligne.c_str(), ios::in);
    if(!fichier_sift)  // si l'ouverture a r�ussi
    {       
		cerr << "Impossible d'ouvrir le fichier sift!" << endl;
		return NULL;
    }


	//R�cup�ration ds coordonn�es du SIFT
	for (int line=0; line<index_ligne;++line)
		getline(fichier_sift,ligne);

	int *sift = new int[128];
	int center_x, center_y;

	fichier_sift >> center_x >> center_y;
	
	for (int i=0; i<128; ++i)
		fichier_sift >> sift[i];

	fichier_sift.close();

	return sift;

}

