#include "symmatrix.h"
using namespace std;


SymMatrix::SymMatrix(int k)
{
	this->coeffs.resize(k*k);
	this->size = k;
	for (int i=0; i<this->size; i++)
		this->coeffs[i] = 0;
}

void SymMatrix::resize(int k)
{
	this->coeffs.resize(k*k);
	this->size = k;
	for (int i=0; i<this->size; i++)
		this->coeffs[i] = 0;
}

double &SymMatrix::operator()(int i, int j)
{
	if (i<=j)
		return this->coeffs[ (this->size)*i + j -i -i*(i-1)/2 ];
	else
		return this->coeffs[ (this->size)*j + i -j -j*(j-1)/2 ];
}

ostream& operator <<(ostream& co, SymMatrix& vec )
{
	int nb=0;
	cout << "Matrice de taille: " << vec.size << endl;
	for (int i=0; i<vec.size; ++i)
	{
		//for (int j=0; j<i; ++j)
		//	cout << "0 ";
		//for (int j=i; j<vec.size; ++j)
		//{
		//	cout << vec.coeffs[nb] << " ";
		//	nb++;
		//}
		for (int j=0; j<vec.size; ++j)
			cout << vec(i,j) << "\t";
		cout << endl;
	}
	return co;
}
