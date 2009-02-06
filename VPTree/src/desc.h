#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum {SIFT};


class Desc
{
public:

	Desc(std::vector<double> position, std::vector<double> coeffs, int type);
	Desc() {type = SIFT;};

	std::vector<double> get_position()
	{ return position; }

	std::vector<double> get_coeffs()
	{ return coeffs; }

	double get_distance_with(Desc &other);
	void get_sum_descs(Desc &other);
	void get_mul_cst(double other);
	void reset();

	void operator*=(double index)
	{this->get_mul_cst(index); }

	void operator+=(Desc &other)
	{this->get_sum_descs(other); }

	double operator-(Desc &other)
	{ return this->get_distance_with(other);}

	std::vector<double> get_kmeans_proba(std::vector<Desc> k_centers);


//private:
	//Position
	std::vector<double> position;

	//Coeffs du descripteur
	std::vector<double> coeffs;

	int type;
};



