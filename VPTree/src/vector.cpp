#include "vector.h"


/**
 * Calcule la distance entre deux features
 **/
double Vector::get_distance_with(Vector &other)
{
	if (type == SIFT && other.type==SIFT)
	{
		double dist = 0;;
		for (unsigned int i=0; i<this->size(); ++i)
		{
			dist += ((*this)[i] - other[i])*((*this)[i] - other[i]);
		}
		return dist;
	}
	else
		exit(3);
}


/**
 * Ajoute un feature au feature courant
 **/
void Vector::add_feature(Vector &other)
{
    if (type==SIFT && other.type==SIFT){
        for (unsigned int i=0; i<this->size(); ++i)
        {
            (*this)[i] += other[i];
        }
    }
    else {
        exit(3);
    }

}

/**
 * Divise un feature par un double
 **/
void Vector::get_mul_cst(double factor)
{
	for (unsigned int i=0; i<this->size(); ++i)
	{
		(*this)[i] *= factor;
	}
}

/**
* Met à 0 tous les coeffs du feature
**/
void Vector::reset()
{
	for (unsigned int i=0; i<this->size(); ++i)
	{
		(*this)[i] = 0;
	}
}


double Vector::compute_second_moment(double val)
{
	int res = 0;
	for (unsigned int i= 0; i<(*this).size(); ++i)
	{
		double temp = (*this)[i] - val;
		res += temp*temp;
	}
	return res;
}

ostream& operator <<(ostream& co, Vector& vec )
{
	cout << "Vecteur de taille: " << vec.size() << endl;
	for (unsigned int i=0; i<vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	return co;
}
