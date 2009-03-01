#ifndef SYMMATRIX
#define SYMMATRIX

#include <iostream>
#include <vector>

using namespace std;

/*
//Utilisation de la classe Matrice Symétrique
	SymMatrix mat(3);
	mat(1,0) = 1;
	mat(2,1) = 2;
	mat(2,2) = 3;
	cout << mat << endl;
*/

class SymMatrix
{

public:
	SymMatrix(int k);
	SymMatrix() {};

	double &operator()(int i, int j);
	void resize(int k);

	friend ostream& operator <<(ostream& co, SymMatrix& f );

private:
	std::vector<double> coeffs;
	int size;



};






#endif