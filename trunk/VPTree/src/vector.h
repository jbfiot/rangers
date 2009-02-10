#pragma once

#include <iostream>
#include <vector>
using namespace std;

enum {SIFT};


/**
 * Classe Vecteur:
 *	Classe d�rivant des std::vector<double> avec des m�thodes pour faire la distance entre deux vecteurs,
 *  la somme, la multiplication par un scalaire...
 **/
class Vector : public std::vector<double>
{
public:
	Vector(int typ=SIFT) {type = SIFT;};

	double get_distance_with(Vector &other);
	void add_feature(Vector &other);
	void get_mul_cst(double other);
	void reset();

	void operator*=(double index)
	{this->get_mul_cst(index); }

	void operator+=(Vector &other)
	{this->add_feature(other); }

	double operator-(Vector &other)
	{ return this->get_distance_with(other);}

	//A impl�menter
	double compute_median() {return 0;}
	double compute_second_moment(double val); //(somme(xi - val)�)

	friend ostream& operator <<(ostream& co, Vector& f );


private:
	int type;

};
