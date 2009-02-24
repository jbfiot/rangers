#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "vector.h"

using namespace std;



class Feature
{
public:

	//Feature(std::vector<double> position, std::vector<double> coeffs, int type);
	Feature(std::vector<double> pos, Vector coef, int typ);
	Feature() {type = SIFT;};

	std::vector<double> get_position()
	{ return position; }

	Vector get_coeffs()
	{ return coeffs; }

	void reset(){ this->coeffs.reset();}

	void operator*=(double index)
	{coeffs *= index; }

	void operator+=(Feature &other)
	{coeffs += other.coeffs; }

	double operator-(Feature &other)
	{ return (this->coeffs - other.coeffs);}

	void get_kmeans_proba( std::vector<Vector> &k_centers, Vector &sigmas, Vector &proba/* Conteneur resultat */)  ;


//private:
	//Position
	std::vector<double> position;

	//Coeffs du feature
	Vector coeffs;

	int type;
	int index_image;

};



