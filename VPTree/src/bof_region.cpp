#include "bof_region.h"


/**
 * Répartition des k_centers en un histogramme
 **/
void Bof_Region::get_nearest_neighbours()
{
	//Resize
    histo_centers.resize(this->centers->size());

    // Initialisation
	histo_centers.reset();
    
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

		histo_centers[nearest] += 1;
    }

}



double Bof_Region::get_distance_region(Bof_Region &other)
{
	Vector distances1;
	distances1.resize(this->centers->size());
	for (int i=0; i<this->histo_centers.size(); ++i)
	{
		//Calcul de la distance de xi à l'ensemble des yj
		double dist = INT_MAX;
		int index1 = this->histo_centers[i];

		for (int j=0; j<other.histo_centers.size(); ++j)
		{
			int index2 = other.histo_centers[j];
			double dist_temp = this->fdb->distances(index1, index2);
			if (dist_temp < dist)
				dist = dist_temp;
		}

		distances1[i] = dist;
	}

	Vector distances2;
	distances2.resize(other.histo_centers.size());
	for (int i=0; i<other.histo_centers.size(); ++i)
	{
		//Calcul de la distance de xi à l'ensemble des yj
		double dist = INT_MAX;
		int index1 = other.histo_centers[i];

		for (int j=0; j<this->histo_centers.size(); ++j)
		{
			int index2 = this->histo_centers[j];
			double dist_temp = this->fdb->distances(index1, index2);
			if (dist_temp < dist)
				dist = dist_temp;
		}

		distances2[i] = dist;
	}

	return (distances1.get_sum() + distances2.get_sum())/(this->features.size() + other.features.size());
}
