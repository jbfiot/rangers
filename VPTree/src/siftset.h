#include <string>
#include <vector>
#include <fstream>

using namespace std;


/**
 *	Classe pour manipuler facilement les points SIFT
 *  (pour ne plus avoir à gérer les accès disque)

 	//Utilisation de la classe SiftSet
	for (int *sift = siftset.begin(); sift != 0; sift = siftset.next())
	{
		//Do stuff with sift
		delete sift;
	}

 **/
class SiftSet
{
public:
	SiftSet(char *name_database, char *name_sifts_files);
	void archive_files();

	int *get_descriptor(double index) const;
	int *operator()(double index);

	int *begin();
	int *next();

	

private:
	char name_database[64];					//Name of the database file
	char name_sifts_files[64];				//Name of SIFT files

	std::vector<std::string> files_names;	//Fichiers SIFT

	char current_file[128];					//Nom du fichier courant
	ifstream fichier_sift;					//Objet fichier SIFT ouvert courant

	double current_sift_index;				//Index du sift courant
	double index_file;						//Index in files_names vector

	


};

