#include "bof_region.h"


/**
 * Répartition des k_centers en un histogramme
 **/
void Bof_Region::compute_nearest_neighbours()
{
	//Resize
	this->nearest_centers.resize(this->features.size());

    // Initialisation
	this->nearest_centers.reset();
    
    // Ajout des proba pour chaque feature du bag of feature. Le tout est divisé par le nombre de features.
	for (unsigned int j=0; j<this->features.size(); j++)
	{
        Feature feat = features[j];
		double dist_min = INT_MAX;
		int nearest = 0;

		for (unsigned int i=0; i<this->centers->size();i++)
		{
			double dist = feat.coeffs - (*(this->centers))[i];
			if (dist < dist_min)
			{
				dist_min = dist;
				nearest = i;
			}
        }

		this->nearest_centers[j] = nearest;
    }

}


/**
 *	Conversion histogramme en vecteur d'index des plus proches centres
 **/
void Bof_Region::set_nearest_centers(Vector &histogram)
{
	for (int i=0; i<histogram.size(); ++i)
		for (int j=0; j<histogram[i]; ++j)
			this->nearest_centers.push_back(i);
}



/**
 *	Conversion histogramme en vecteur d'index des plus proches centres
 **/
void Bof_Region::get_histogram(Vector &histogram)
{
	//Initialisation à 0 de l'histogramme
	histogram.resize(this->centers->size());
	histogram.reset();

	for (int i=0; i<this->nearest_centers.size(); ++i)
		histogram[this->nearest_centers[i]]++;
}



double Bof_Region::get_distance_region(Bof_Region &other)
{
	Vector distances1;
	distances1.resize(this->nearest_centers.size());
	for (int i=0; i<this->nearest_centers.size(); ++i)
	{
		//Calcul de la distance de xi à l'ensemble des yj
		double dist = INT_MAX;
		int index1 = this->nearest_centers[i];

		for (int j=0; j<other.nearest_centers.size(); ++j)
		{
			int index2 = other.nearest_centers[j];
			double dist_temp = this->fdb->distances(index1, index2);
			if (dist_temp < dist)
				dist = dist_temp;
		}

		distances1[i] = dist;
	}

	Vector distances2;
	distances2.resize(other.nearest_centers.size());
	for (int i=0; i<other.nearest_centers.size(); ++i)
	{
		//Calcul de la distance de xi à l'ensemble des yj
		double dist = INT_MAX;
		int index1 = other.nearest_centers[i];

		for (int j=0; j<this->nearest_centers.size(); ++j)
		{
			int index2 = this->nearest_centers[j];
			double dist_temp = this->fdb->distances(index1, index2);
			if (dist_temp < dist)
				dist = dist_temp;
		}

		distances2[i] = dist;
	}

	return (distances1.get_sum() + distances2.get_sum())/(this->nearest_centers.size() + other.nearest_centers.size());
}
