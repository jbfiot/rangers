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



