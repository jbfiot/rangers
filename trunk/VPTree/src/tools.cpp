#include "tools.h"
#include <time.h>
#include <iostream>
#include "siftset.h"


/**
 * Selectionne une liste aleatoire de k nombres entre 1 et n (n>=k)
 **/
int *get_random_set_indexes(int k,int n)
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

