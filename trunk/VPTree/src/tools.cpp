#include "tools.h"
#include <time.h>
#include <iostream>
#include <time.h>
#include <vector>

#include <algorithm>
using namespace std;



/**
 * Selectionne une liste aleatoire de k nombres entre 1 et n (n>=k)
 **/
void get_random_set_indexes(int k,int n, std::vector<int> &indexes)
{
	indexes.resize(k);
	for (int i=0; i<k; ++i)
	{
		int index;
		while (1)
		{
			index = rand()%n;

			vector<int>::iterator p = find(indexes.begin(),indexes.begin()+i,index);
			if (p == indexes.begin()+i)
				break;
		}

		indexes[i] = index;
	}

}






double strtodouble(const string& what)
{
	// La fonction "double atof( char* ) réalise exactement ceci :
	// atof( what.c_str() )
	// http://www.cplusplus.com/reference/clibrary/cstdlib/atof.html
	// http://www.cplusplus.com/reference/string/string/c_str.html
	istringstream instr(what);
	double val;
	instr >> val;
	return val;
}
