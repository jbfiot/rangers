#include "Feature.h"

/**
*
* Codes d'erreurs :
* - 3 : erreur de type de feature
**/


Feature::Feature(std::vector<double> pos, std::vector<double> coef, int typ){
	position = pos;
	coeffs = coef;
	type = typ;
}


/**
* Met à 0 tous les coeffs du feature
**/
void Feature::reset()
{
	for (unsigned int i=0; i<coeffs.size(); ++i)
	{
		coeffs[i] = 0;
	}
}


/**
 * Calcule la distance entre deux features
 **/
double Feature::get_distance_with(Feature &other)
{
	if (type == SIFT && other.type==SIFT)
	{
		double dist = 0;;
		for (unsigned int i=0; i<coeffs.size(); ++i)
		{
			dist += (coeffs[i] - other.coeffs[i])*(coeffs[i] - other.coeffs[i]);
		}
		return dist;
	}
	else {
		exit(3);
	}
}


/**
 * Ajoute un feature au feature courant
 **/
void Feature::add_feature(Feature &other)
{
    if (type==SIFT && other.type==SIFT){
        for (unsigned int i=0; i<coeffs.size(); ++i)
        {
            coeffs[i] += other.coeffs[i];
        }
    }
    else {
        exit(3);
    }

}



/**
 * Divise un feature par un double
 **/
void Feature::get_mul_cst(double factor)
{
	for (unsigned int i=0; i<coeffs.size(); ++i)
	{
		coeffs[i] *= factor;
	}
}


/**
 * Calcule les proba d'appartenance aux k-classes du k-means.
 **/
std::vector<double> Feature::get_kmeans_proba(std::vector<Feature> k_centers){
    // Formule : proba appartenance classe-k = distance au centre k divisee par la somme des distances aux centres.
    std::vector<double> proba;
    double sum=0;
    for (unsigned int i=0; i<k_centers.size(); i++){
        proba[i] = 1-(*this - k_centers[i]);
        sum+=proba[i];
    }
    for (unsigned int i=0; i<k_centers.size(); i++){
        proba[i] = proba[i]/sum;
    }
    return proba;

}






