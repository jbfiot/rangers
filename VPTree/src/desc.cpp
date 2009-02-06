#include "desc.h"

Desc::Desc(std::vector<double> pos, std::vector<double> coef, int typ){
	position = pos;
	coeffs = coef;
	type = typ;
}




/**
* Met à 0 tous les coeffs du SIFT
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
	if (type == SIFT)
	{
		double dist = 0;;
		for (unsigned int i=0; i<coeffs.size(); ++i)
		{
			dist += (coeffs[i] - other.coeffs[i])*(coeffs[i] - other.coeffs[i]);
		}
		return dist;
	}
	else
		return 0;
}


/**
 * Ajoute un descripteur au descripteur courant
 **/
void Desc::get_sum_descs(Desc &other)
{
	for (unsigned int i=0; i<coeffs.size(); ++i)
	{
		coeffs[i] += other.coeffs[i];
	}
}



/**
 * Divise un sift par un entier
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
    if (type == SIFT) {
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
    }
    else {
        exit(3);

    }



}



