#include "vector.h"


/**
 * Calcule la distance entre deux features
 **/
double Vector::get_distance_with (Vector &other) const
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
// A verifier mais ca il me semble que ce serait teeeeeellement plus rapide avec des iterateurs. La ca doit etre tres tres lent.
// Est-ce qu'il ne faudrait pas verifier que this et other ont la meme taille ?
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
// voir plus haut : iterateurs = mieux
{
	for (unsigned int i=0; i<this->size(); ++i)
	{
		(*this)[i] *= factor;
	}
}

/**
* Met e 0 tous les coeffs du feature
**/
void Vector::reset()
// voir plus haut : iterateurs = mieux
{
	for (unsigned int i=0; i<this->size(); ++i)
	{
		(*this)[i] = 0;
	}
}


double Vector::compute_median () const
{  
	Vector tmp = (*this);
	unsigned int size = tmp.size();
	sort(tmp.begin(), tmp.end());
	unsigned int mid = size/2;
	return size % 2 == 0 ? (tmp[mid] + tmp[mid-1]) / 2 : tmp[mid];
}


double Vector::compute_second_moment (double val) const
{
	double res = 0;
	for (unsigned int i= 0; i<(*this).size(); ++i)
	{
		double temp = (*this)[i] - val;
		res += temp*temp;
	}

	return res;
}

ostream& operator <<(ostream& co, const Vector& vec )
{
	cout << "Vecteur de taille: " << vec.size() << endl;
	for (unsigned int i=0; i<vec.size(); ++i)
	{
		cout << vec[i] << " ";
	}
	return co;
}
