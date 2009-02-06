#include "desc.h"

/**
*
* Codes d'erreurs :
* - 3 : erreur de type de descripteur
**/


Desc::Desc(std::vector<double> pos, std::vector<double> coef, int typ){
	position = pos;
	coeffs = coef;
	type = typ;
}


/**
* Met à 0 tous les coeffs du descripteur
**/
void Desc::reset()
{
	for (unsigned int i=0; i<coeffs.size(); ++i)
	{
		coeffs[i] = 0;
	}
}


/**
 * Calcule la distance entre deux descripteurs
 **/
double Desc::get_distance_with(Desc &other)
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
 * Ajoute un descripteur au descripteur courant
 **/
void Desc::get_sum_descs(Desc &other)
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
 * Divise un descripteur par un entier
 **/
void Desc::get_mul_cst(double factor)
{
	for (unsigned int i=0; i<coeffs.size(); ++i)
	{
		coeffs[i] *= factor;
	}
}


/**
 * Calcule les proba d'appartenance aux k-classes du k-means.
 **/
std::vector<double> Desc::get_kmeans_proba(std::vector<Desc> k_centers){
    // Formule : proba appartenance classe-k = distance au centre k divisee par la somme des distances aux centres.
    std::vector<double> proba;
    double sum=0;
    for (unsigned int i=0; i<k_centers.size(); i++){
        proba[i] = *this - k_centers[i];
        sum+=proba[i];
    }
    for (unsigned int i=0; i<k_centers.size(); i++){
        proba[i] = proba[i]/sum;
    }
    return proba;

}






