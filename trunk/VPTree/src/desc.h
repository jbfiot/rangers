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
	
	std::vector<double> get_position()
	{ return position; }

	std::vector<double> get_coeffs()
	{ return coeffs; }

	double get_distance_with(Desc &other);
	void get_sum_descs(Desc &other);
	void get_mul_cst(double other);
	void reset();

	std::vector<double> operator*=(double index)
	{this->get_mul_cst(index); }

	std::vector<double> operator+=(Desc &other)
	{this->get_sum_descs(other); }

	std::vector<double> operator-(Desc &other)
	{ return this->get_distance_with(other);}


private:
	//Position
	std::vector<double> position;

	//Coeffs du descripteur
	std::vector<double> coeffs;

	int type;
};
