#include <iostream>
#include <fstream>
#include "siftset.h"

#include <algorithm>

#include <string>
#include <vector>

#include <time.h>

using namespace std;



std::vector<double> SiftSet::operator ()(double index)
{
	return (this)->get_descriptor(index);
}

/**
*	Constructeur => prend un fichier de base de donn�es et le fichier o� il y a le nom de tous les fichiers
**/
SiftSet::SiftSet(char *name_base, char *name_sifts)
{
	srand ( time(NULL) );

	files_names.clear();

	memcpy(name_database, name_base, sizeof(name_database));
	memcpy(name_sifts_files, name_sifts, sizeof(name_sifts_files));

	current_sift_index = 0;

	archive_files();
	compte_lignes();
}


/**
 * Calcule la distance entre deux sifts
 **/
double SiftSet::get_distance(std::vector<double> sift1, std::vector<double> sift2)
{
	double dist = 0;;
	for (int i=0; i<sift1.size(); ++i)
	{
		dist += (sift1[i] - sift2[i])*(sift1[i] - sift2[i]);
	}
	return dist;
}

/**
 * Ajoute un sift � un autre
 **/
void SiftSet::ajoute(std::vector<double> &a_modif, std::vector<double> &correction)
{
	for (int i=0; i<a_modif.size(); ++i)
	{
		a_modif[i] += correction[i];
	}

}


/**
 * Divise un sift par un entier
 **/
void SiftSet::divise(std::vector<double> &a_modif, double n)
{
	for (int i=0; i<a_modif.size(); ++i)
	{
		a_modif[i] /= n;
	}

}


/**
 * Met � 0 tous les coeffs du SIFT
 **/
template <typename T>
void SiftSet::reset(std::vector<T> &a_modif)
{
	for (int i=0; i<a_modif.size(); ++i)
	{
		a_modif[i] = 0;
	}

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
*	Compte le noombre de points SIFTs total
**/
void SiftSet::compte_lignes()
{
	ifstream fichier_database(name_database, ios::in);  // on ouvre le fichier en lecture

	if(!fichier_database)  // si l'ouverture a r�ussi
	{       
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		return;
	}

	std::string ligne; 
	double lignes = 0;
	while(getline(fichier_database,ligne)) 
		lignes++;

	nb_sifts = lignes;
}



/**
*	Initialise l'it�rateur
**/
std::vector<double> SiftSet::begin()
{
	std::vector<double> sift;

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
		return sift;
	}

	//On zappe la premi�re ligne
	std::string ligne;
	getline(fichier_sift, ligne);

	//R�cup�ration ds coordonn�es du SIFT
	int center_x, center_y;

	fichier_sift >> center_x >> center_y;

	sift.resize(128);

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
std::vector<double> SiftSet::next()
{
	//On continue � lire le fichier pr�c�dent
	//std::string line;
	std::vector<double> sift;

	if (fichier_sift.eof())
	{
		if (index_file == files_names.size())
			return sift;

		std::string sift_file_name = files_names[index_file];
		memcpy(current_file, sift_file_name.c_str(), sizeof(current_file));

		//Ouverture du fichier sift
		fichier_sift.close();
		fichier_sift.clear();

		fichier_sift.open(current_file, ios::in);

		if(!fichier_sift.is_open())  // si l'ouverture n'a pas r�ussi
		{       
			cerr << endl << "Impossible d'ouvrir le fichier sift!" << endl;
			return sift;
		}

		//On zappe la premi�re ligne
		std::string ligne;
		getline(fichier_sift, ligne);

		index_file++;
	}


	//R�cup�ration ds coordonn�es du SIFT
	int center_x, center_y;

	fichier_sift >> center_x >> center_y;

	sift.resize(128);

	for (int i=0; i<128; ++i)
		fichier_sift >> sift[i];

	current_sift_index ++;

	return sift;
}




/**
*	R�cup�re les coordonn�es du SIFT num�ro index
**/
std::vector<double> SiftSet::get_descriptor(double index) const
{
	std::vector<double> sift;

	//Ouverture du fichier database
	ifstream fichier_database(name_database, ios::in);
	if(!fichier_database)  // si l'ouverture a r�ussi
	{       
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		return sift;
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
		return sift;
	}


	//R�cup�ration ds coordonn�es du SIFT
	for (int line=0; line<index_ligne;++line)
		getline(fichier_sift,ligne);

	int center_x, center_y;

	fichier_sift >> center_x >> center_y;

	sift.resize(128);

	for (int i=0; i<128; ++i)
		fichier_sift >> sift[i];

	fichier_sift.close();

	return sift;

}


void SiftSet::do_k_means(int k, std::vector<double> *centers)
{
	//Initialisation des centres au pif
	for (int i=0; i<k; ++i)
	{
		for (int j=0; j<128; ++j)
		{
			//Coords des SIFTs entre 0 et 100?
			centers[i].push_back( rand()*100./RAND_MAX );
		}
	}

	//S�lection des indexes des points SIFTs au pif
	int indexes[SAMPLE_LENGTH_FOR_K_MEANS];
	for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
	{
		int index;
		while (1)
		{
			index = rand()%nb_sifts;

			int *p = find(indexes,indexes+i,index);
			if (p == indexes+i)
				break;
		}

		indexes[i] = index;
	}

	// On met les tous les SIFTs s�lectionn�s dans une liste
	std::vector<double> sifts_list[SAMPLE_LENGTH_FOR_K_MEANS];
	for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
	{
		sifts_list[i] = get_descriptor(indexes[i]);
	}

	//K-MEANS...
	int nb_iters = 1;
	int appartenances[SAMPLE_LENGTH_FOR_K_MEANS];
	std::vector<int> numbers(k);
	while (1)
	{
		cout << "Iteration number " << nb_iters << endl;

		bool has_changed = false;
		// Assigner chaque point � une classe
		for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
		{
			std::vector<double> sift = sifts_list[i];
			int index_classe=0;
			double best_dist = INT_MAX;
			for (int j=0; j<k; ++j)
			{
				double dist = get_distance(centers[j], sift);
				if (dist<best_dist)
				{
					best_dist = dist;
					index_classe = j;
				}
			}
			if ((!has_changed) && (appartenances[i] != index_classe))
				has_changed = true;
			appartenances[i] = index_classe;
		}

		if (!has_changed)
			break;
		
		// Calculer le barycentre de chaque classe
		for (int j=0; j<k; ++j)
			reset(centers[j]);
		reset(numbers);
		for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
		{
			int classe = appartenances[i];
			ajoute(centers[classe], sifts_list[i]);
			numbers[classe]++;
		}
		for (int j=0; j<k; ++j)
			divise(centers[j], numbers[j]);

		nb_iters++;
	
	}


}
