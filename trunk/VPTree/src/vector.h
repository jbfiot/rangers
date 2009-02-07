#pragma once

#include <vector>
using namespace std;

enum {SIFT};


/**
 * Classe Vecteur:
 *	Classe dérivant des std::vector<double> avec des méthodes pour faire la distance entre deux vecteurs,
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

	//A implémenter
	double compute_median() {return 0;}
	double compute_second_moment(double val) {return 0;} //(somme(xi - val)²)


private:
	int type;

};
