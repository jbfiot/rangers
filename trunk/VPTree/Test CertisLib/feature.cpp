#include "Feature.h"
#include <math.h>

/**
*
* Codes d'erreurs :
* - 3 : erreur de type de feature
**/


//Feature::Feature(std::vector<double> pos, std::vector<double> coef, int typ){
//	position = pos;
//	coeffs = (Vector) Vector(coef);
//	type = typ;
//}

Feature::Feature(std::vector<double> pos, Vector coef, int typ){
	position = pos;
	coeffs = coef;
	type = typ;
}



/**
 * Calcule les proba d'appartenance aux k-classes du k-means.
 **/
void Feature::get_kmeans_proba( std::vector<Vector> &k_centers, Vector &sigmas, Vector &proba/* Conteneur resultat */)  {
    // Formule : proba appartenance classe-k = distance au centre k divisee par la somme des distances aux centres.
    double sum=0;
    proba.resize(k_centers.size());
    for (int i=0; i<k_centers.size(); i++){
		double dist = this->coeffs.get_distance_with_chi2(k_centers[i]);
		proba[i] = exp(-1 * dist / sigmas[i]);
        sum+=proba[i];
    }
	
    for (unsigned int i=0; i<k_centers.size(); i++){
        proba[i] = proba[i]/sum;
    }

}


