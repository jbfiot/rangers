#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

enum {SIFT};


/**
 * Classe Vecteur:
 *	Classe derivant des std::vector<double> avec des methodes pour faire la distance entre deux vecteurs,
 *  la somme, la multiplication par un scalaire...
 **/
class Vector : public std::vector<double>
{
public:
	Vector(int typ=SIFT) {type = SIFT;};

// Une classe fille herite de tout, sauf :
// 1) des constructeurs et du destructeur
// 2) des classe amie (friends)
// 3) de l'operateur =
// Des bogues incomprehensibles vont apparaitre si au moins les constructeurs
// par defaut et par copie, ainsi que l'operateur = ne sont pas redefinis.

	double get_distance_with(Vector &other) const;
	void add_feature(Vector &other);
	void get_mul_cst(double other);
	void reset();

	void operator*=(double index)
	{this->get_mul_cst(index); }

	void operator+=(Vector &other)
	{this->add_feature(other); }

	double operator-(Vector &other)
	{ return this->get_distance_with(other);}

	//A implementer
	double compute_median();
	double compute_second_moment(double val) const; //(somme(xi - val)e)

	friend ostream& operator <<(ostream& co, Vector& f );


private:
	int type;

};
