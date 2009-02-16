#include "tools.h"
#include "feature.h"
#include "bof.h"
#include "vector.h"

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

/***
 ** calcul des regions : 4 régions par image
**/

vector<Bof> get_all_regions_subsets( const vector<Feature>& res )
{
	int maxX=0, maxY=0;
	int minX=10000, minY=10000;
	int ind_max=0, ind_min=0;
	vector<Feature> feats_1, feats_2, feats_3, feats_4;
	vector<Bof> all_regions_in_image;

	for (int i=0; i<res.size(); i++)
	{
		if (maxX<res[i].position[0] && maxY<res[i].position[1])
		{
			maxX=res[i].position[0];
			maxY=res[i].position[1];
			ind_max=i;
		}
		if (minX>res[i].position[0] && minY>res[i].position[1])
		{
			minX=res[i].position[0];
			minY=res[i].position[1];
			ind_min=i;
		}
	}

	for (int j=0; j<res.size(); j++)
	{
		if (res[j].position[0]>(res[ind_max].position[0]-res[ind_min].position[0])/2 &&
			res[j].position[1]>(res[ind_max].position[1]-res[ind_min].position[1])/2)
			feats_1.push_back(res[j]);
		else if (res[j].position[0]>(res[ind_max].position[0]-res[ind_min].position[0])/2 &&
			res[j].position[1]<=(res[ind_max].position[1]-res[ind_min].position[1])/2)
			feats_2.push_back(res[j]);
		else if (res[j].position[0]<=(res[ind_max].position[0]-res[ind_min].position[0])/2 &&
			res[j].position[1]>(res[ind_max].position[1]-res[ind_min].position[1])/2)
			feats_3.push_back(res[j]);
		else
			feats_4.push_back(res[j]);

	}

	all_regions_in_image.push_back(Bof(feats_1));
	all_regions_in_image.push_back(Bof(feats_2));
	all_regions_in_image.push_back(Bof(feats_3));
	all_regions_in_image.push_back(Bof(feats_4));

	return all_regions_in_image;
}

