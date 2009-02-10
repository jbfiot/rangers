#include <iostream>
#include <fstream>
#include "siftset.h"

#include <algorithm>

#include <string>
#include <vector>

#include <time.h>

using namespace std;



void display(std::vector<double> sift)
{
	for (int i=0; i<sift.size();++i)
	{
		cout << sift[i] << " ";
	}
	cout << endl;
}





Feature SiftSet::operator ()(double index)
{
	return (this)->get_feature(index);
}

/**
 *	Constructeur => prend un fichier de base de données et le fichier où il y a le nom de tous les fichiers
 **/
SiftSet::SiftSet(char *name_base, char *name_sifts)
{
	files_names.clear();

	memcpy(name_database, name_base, sizeof(name_database));
	memcpy(name_sifts_files, name_sifts, sizeof(name_sifts_files));

	current_sift_index = 0;

	archive_files();
	compte_lignes();
}


/**
 *	Met tous les noms des fichiers .SIFT dans un vecteur
 **/
void SiftSet::archive_files()
{
	ifstream fichier_database(name_sifts_files, ios::in);  // on ouvre le fichier en lecture

	cout << name_sifts_files <<endl;

	if(!fichier_database)  // si l'ouverture a réussi
	{
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		exit(1);
	}

	std::string ligne;

	while(getline(fichier_database,ligne)) {
		files_names.push_back(ligne);
	//	cout << ligne<<endl;
	}

	nb_images = files_names.size();
}


/**
 *	Compte le noombre de points SIFTs total
 **/
void SiftSet::compte_lignes()
{
	ifstream fichier_database(name_database, ios::in);  // on ouvre le fichier en lecture

	if(!fichier_database)  // si l'ouverture a réussi
	{
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		exit(1);
	}

	std::string ligne;
	double lignes = 0;
	while(getline(fichier_database,ligne))
		lignes++;

	nb_sifts = lignes;
}



/**
 *	Initialise l'itérateur
 **/
Feature SiftSet::begin()
{
	Feature sift;

	if (fichier_sift.is_open())
	{
		fichier_sift.close();
		fichier_sift.clear();
	}

	std::string sift_file_name = files_names[0];
	memcpy(current_file, sift_file_name.c_str(), sizeof(current_file));

	//Ouverture du fichier sift
	char current_file1[] = "../Samples/image0.sift";

	fichier_sift.open(current_file, ios::in);

	cout << "'" << current_file1 <<"'" <<endl;

	if(!fichier_sift)  // si l'ouverture n'a pas réussi
	{
		cerr << "Impossible d'ouvrir le fichier sift!" << endl;
		exit(2);
	}

	//On zappe la première ligne
	std::string ligne;
	getline(fichier_sift, ligne);

	//Récupération ds coordonnées du SIFT
	int center_x, center_y;

	sift.position.resize(2);
	sift.coeffs.resize(128);

	fichier_sift >> sift.position[0] >> sift.position[1];
	for (int i=0; i<128; ++i)
		fichier_sift >> sift.coeffs[i];

	//fichier_sift.close();

	current_sift_index = 1;
	index_file = 1;

	return sift;
}


/**
 *	Renvoie le SIFT suivant (après initialisation de l'itérateur)
 **/
Feature SiftSet::next()
{
	//On continue à lire le fichier précédent
	//std::string line;
	Feature sift;

	if (fichier_sift.eof())
	{
		if (index_file == getnbimages())
			return sift;

		std::string sift_file_name = files_names[index_file];
		memcpy(current_file, sift_file_name.c_str(), sizeof(current_file));

		//Ouverture du fichier sift
		fichier_sift.close();
		fichier_sift.clear();

		fichier_sift.open(current_file, ios::in);

		if(!fichier_sift.is_open())  // si l'ouverture n'a pas réussi
		{
			cerr << endl << "Impossible d'ouvrir le fichier sift!" << endl;
			exit(2);
		}

		//On zappe la première ligne
		std::string ligne;
		getline(fichier_sift, ligne);

		index_file++;
	}


	//Récupération ds coordonnées du SIFT
	int center_x, center_y;

	sift.coeffs.resize(128);
	sift.position.resize(2);

	fichier_sift >> sift.position[0] >> sift.position[1];

	for (int i=0; i<128; ++i)
		fichier_sift >> sift.coeffs[i];

	current_sift_index ++;

	return sift;
}




/**
 *	Récupère les coordonnées du SIFT numéro index
 **/
Feature SiftSet::get_feature(double index) const
{
	assert(index < getnbsift());

	Feature sift;

	//Ouverture du fichier database
	ifstream fichier_database(name_database, ios::in);
	if(!fichier_database)  // si l'ouverture a réussi
	{
		cerr << "Impossible d'ouvrir le fichier database!" << endl;
		exit(1);
	}
	std::string ligne;
	int index_ligne;

	//Récupération du fichier et de l'offset où se trouve le sift voulu
	for (int line=0; line<index; ++line)
		getline(fichier_database,ligne);

	fichier_database >> ligne >> index_ligne;
	fichier_database.close();


	//Ouverture du fichier sift
	ifstream fichier_sift(ligne.c_str(), ios::in);
	if(!fichier_sift)  // si l'ouverture a réussi
	{
		cerr << "Impossible d'ouvrir le fichier sift!" << endl;
		exit(2);
	}


	//Récupération ds coordonnées du SIFT
	for (int line=0; line<index_ligne;++line)
		getline(fichier_sift,ligne);

	int center_x, center_y;

	sift.coeffs.resize(128);
	sift.position.resize(2);
	fichier_sift >> sift.position[0] >> sift.position[1];

	for (int i=0; i<128; ++i)
		fichier_sift >> sift.coeffs[i];

	fichier_sift.close();

	return sift;

}


/**
 *	Récupère tous les SIFTs dans une image donnée
 **/
std::vector<Feature> SiftSet::get_sifts_in_image(int img_index)
{
	assert(img_index < files_names.size());

	//Nom du fichier image
	std::string filename = files_names[img_index];

	//Ouverture du fichier
	ifstream fichier_sift(filename.c_str(), ios::in);

	if(!fichier_sift.is_open())  // si l'ouverture n'a pas réussi
	{
		cerr << endl << "Impossible d'ouvrir le fichier sift!" << endl;
		exit(2);
	}

	//Résultat : tableau de SIFTs
	std::vector<Feature> result;

	//On zappe la première ligne
	std::string ligne;
	getline(fichier_sift, ligne);

	int center_x, center_y;

	while (!fichier_sift.eof())
	{
		Feature sift;

		sift.coeffs.resize(128);
		sift.position.resize(2);

		//Récupération ds coordonnées du SIFT
		fichier_sift >> sift.position[0] >> sift.position[1];

		for (int i=0; i<128; ++i)
			fichier_sift >> sift.coeffs[i];

		result.push_back(sift);
	}

	return result;
}








/**
 *	Applique l'algorithme des K-Means sur le SiftSet
 **/
std::vector<Feature> SiftSet::do_k_means(int k)
{
	assert(k<SAMPLE_LENGTH_FOR_K_MEANS && SAMPLE_LENGTH_FOR_K_MEANS<getnbsift());

	std::vector<Feature> centers(k);

	//Initialisation des centres au pif
	for (int i=0; i<k; ++i)
	{
		for (int j=0; j<128; ++j)
		{
			//Coords des SIFTs entre 0 et 100?
			centers[i].coeffs.push_back( rand()*100./RAND_MAX );
		}
	}

	//Sélection des indexes des points SIFTs au pif
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

	// On met les tous les SIFTs sélectionnés dans une liste
	Feature sifts_list[SAMPLE_LENGTH_FOR_K_MEANS];
	for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
	{
		sifts_list[i] = get_feature(indexes[i]);
	}

	//K-MEANS...
	int nb_iters = 1;
	int appartenances[SAMPLE_LENGTH_FOR_K_MEANS];
	std::vector<int> numbers(k);
	while (1)
	{
		cout << "Iteration number " << nb_iters << endl;

		bool has_changed = false;
		// Assigner chaque point à une classe
		for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
		{
			Feature sift = sifts_list[i];
			int index_classe=0;
			double best_dist = INT_MAX;
			for (int j=0; j<k; ++j)
			{
				double dist = centers[j] - sift;
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
			centers[j].reset();

		for (int j=0; j<k; ++j)
			numbers[j] = 0;

		for (int i=0; i<SAMPLE_LENGTH_FOR_K_MEANS; ++i)
		{
			int classe = appartenances[i];
			centers[classe] += sifts_list[i];
			numbers[classe]++;
		}

		for (int j=0; j<k; ++j)
			centers[j] *= 1./numbers[j];

		nb_iters++;

	}

	return centers;


}
