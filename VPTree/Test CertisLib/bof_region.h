#ifndef BOF_REGION
#define BOF_REGION

#include "feature.h"

#include <string>
#include <vector>
#include <assert.h>

#include "feature_db.h"



/**
 * Classe Bof = Bag-of-features
 **/
class Bof_Region
{
public:

	//Construction d'une région à partir de SIFTs
	Bof_Region(std::vector<int> feature_indexes, Feature_db *fdb_in, std::vector<Vector> *k_centers)
	{
		this->centers = k_centers;
		this->fdb = fdb_in;

		//Récupération des coordonnées de tous les features
		this->fdb->get_features_by_indexes(feature_indexes, this->features);

		//Construction de l'histogramme
		this->compute_nearest_neighbours();
	}

	//Construction d'une région directement à partir d'un histogramme
	Bof_Region(Vector histo_centers_in, Feature_db *fdb_in)
	{
		this->fdb = fdb_in;
		this->set_nearest_centers(histo_centers_in);
	}

	//Dummy constructor
	Bof_Region(){};

	// méthode permettant d'initialiser le contenu du Bof_Region
	void init_Bof_Region(std::vector<Feature> feature_indexes,
		Feature_db *fdb_in,
		std::vector<Vector> *k_centers)
	{
		features = feature_indexes;
		fdb = fdb_in;
		centers = k_centers;

		this->compute_nearest_neighbours();
	}


	//Conversion histogramme => plus proches centres
	void set_nearest_centers(Vector &histo_centers_in);

	//Conversion histogramme <= plus proches centres
	void get_histogram(Vector &histo);

	//Distance entre deux Régions
	double operator-(Bof_Region &other)
	{ return this->get_distance_region(other);}

	// Méthode pour obtenir la repartition dans les k classes du k-means.
	void get_kmeans_proba(Vector &proba) ;

	double get_distance_region(Bof_Region &other);



	Vector nearest_centers;

	std::vector<Feature> features;


	void compute_nearest_neighbours();

private:
	Feature_db *fdb;


	std::vector<Vector> *centers;

};




#endif
