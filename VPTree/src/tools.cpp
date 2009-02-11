#include "tools.h"
#include <time.h>
#include <iostream>
#include <time.h>

#include <algorithm>
using namespace std;



/**
 * Selectionne une liste aleatoire de k nombres entre 1 et n (n>=k)
 **/
int *get_random_set_indexes(int k,int n)
// Est-ce que renvoyer un int* est vraiment judicieux ? 
// Cette fonction nécessite de réaliser une allocation mémoire 
// potentiellement importante à chaque fois.
// Est-ce qu'il ne serait pas plus interessant de prendre en argument un vector<int>& 
// et de ne modifier sa taille seulement dans les cas indispensables ?
{
	int *indexes = new int[k];
	for (int i=0; i<k; ++i)
	{
		int index;
		while (1)
		{
			index = rand()%n;

			int *p = find(indexes,indexes+i,index);
			if (p == indexes+i)
				break;
		}

		indexes[i] = index;
	}
	return indexes;
}

