#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum {SIFT};


class Feature
{
public:

	Feature(std::vector<double> position, std::vector<double> coeffs, int type);
	Feature() {type = SIFT;};

	std::vector<double> get_position()
	{ return position; }

	std::vector<double> get_coeffs()
	{ return coeffs; }

	double get_distance_with(Feature &other);
	void add_feature(Feature &other);
	void get_mul_cst(double other);
	void reset();

	void operator*=(double index)
	{this->get_mul_cst(index); }

	void operator+=(Feature &other)
	{this->add_feature(other); }

	double operator-(Feature &other)
	{ return this->get_distance_with(other);}

	std::vector<double> get_kmeans_proba(std::vector<Feature> k_centers);


//private:
	//Position
	std::vector<double> position;

	//Coeffs du feature
	std::vector<double> coeffs;

	int type;
};



