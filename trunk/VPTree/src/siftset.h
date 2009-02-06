#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <assert.h>

#include "Feature.h"

using namespace std;


#define SAMPLE_LENGTH_FOR_K_MEANS 100



class SiftSet
{
public:
	SiftSet(char *name_database, char *name_sifts_files);

	//Pour l'initialisation
	void archive_files();
	void compte_lignes();

	int getnbsift() const {return nb_sifts;};
	double get_distance(std::vector<double> sift1, std::vector<double> sift2);
	void ajoute(std::vector<double> &a_modif, std::vector<double> &correction);
	void divise(std::vector<double> &a_modif, double n);

	template <typename T>
	void reset(std::vector<T> &a_modif);

	//Pour obtenir un SIFT à partir de son index
	Feature get_feature(double index) const;
	Feature operator()(double index);
	std::vector<Feature> get_sifts_in_image(int img_index);

	//Pour itérer sur tous les sifts
	Feature begin();
	Feature next();

	//Pour faire un K-Means sur l'espace des SIFTs
	void do_k_means(int k, Feature *centers);



private:
	char name_database[64];					//Name of the database file
	char name_sifts_files[64];				//Name of SIFT files

	std::vector<std::string> files_names;	//Fichiers SIFT

	char current_file[128];					//Nom du fichier courant
	ifstream fichier_sift;					//Objet fichier SIFT ouvert courant

	double current_sift_index;				//Index du sift courant
	double index_file;						//Index in files_names vector

	int nb_sifts;							//Nombre de points SITFs total

};


void display(std::vector<double>);


