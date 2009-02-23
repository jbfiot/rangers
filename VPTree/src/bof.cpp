#include "bof.h"


void Bof::get_kmeans_proba(std::vector<Vector> &k_centers, Vector &proba)  {
    Vector proba_j;
    proba.resize(k_centers.size());

    // Initialisation
    for (unsigned int i=0; i<k_centers.size();i++)
        proba[i]=0;
    
    // Ajout des proba pour chaque feature du bag of feature. Le tout est divisé par le nombre de features.
    for (unsigned int j=0; j<features.size(); j++){
        features[j].get_kmeans_proba(k_centers, proba_j);
        for (unsigned int i=0; i<k_centers.size();i++){
            proba[i] += proba_j[i];
        }

    }
    proba*=1./features.size();


}


double Bof::get_distance_region(Bof &other)
{
	Vector distances;

	for (int i=0; i<this->features.size(); ++i)
	{
		//Calcul de la distance de xi à l'ensemble des yj
		double dist = INT_MAX;
		Feature feat = this->features[i];

		for (int j=0; j<other.features.size(); ++j)
		{
			double dist_temp = other.features[j] - feat;
			if (dist_temp < dist)
				dist = dist_temp;		
		}
	}

	return distances.get_min();
}
