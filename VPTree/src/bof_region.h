#ifndef BOF_REGION
#define BOF_REGION

#include "Feature.h"

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

	Bof_Region(std::vector<int> feature_indexes, Feature_db *fdb, std::vector<Vector> *k_centers)
	{
		this->centers = k_centers;
		this->get_nearest_neighbours();

		//Récupération des coordonnées de tous les features
		fdb->get_features_by_indexes(feature_indexes, this->features);
	}

	// Méthode pour obtenir la repartition dans les k classes du k-means.
	void get_kmeans_proba(Vector &proba) ;

	double get_distance_region(Bof_Region &other);

	

	//private:
	
	//std::vector<int> features;

	//Pour chaque feature, on choisit le centre le plus proche, et on fait l'histogramme
	Vector histo_centers;

private:
	Feature_db *fdb;
	void get_nearest_neighbours();

	std::vector<Vector> *centers;
	std::vector<Feature> features;
	
};




#endif
