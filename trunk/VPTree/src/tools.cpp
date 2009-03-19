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
	// La fonction "double atof( char* ) realise exactement ceci :
	// atof( what.c_str() )
	// http://www.cplusplus.com/reference/clibrary/cstdlib/atof.html
	// http://www.cplusplus.com/reference/string/string/c_str.html
	istringstream instr(what);
	double val;
	instr >> val;
	return val;
}

/***
 ** calcul des regions : une région est formée d'un ou plusieurs carres de taille nb_pixels
**/

void get_all_regions_subsets( const vector<Feature>& res, vector<Bof>& all_regions_in_image, int nb_pixels )
{
	int maxX=0, maxY=0;
	int i=0, j=0, k=0, u=0, v=0, w=0;
	int itX=0, itY=0;
	vector<Feature> feats;

	for (i=0; i<res.size(); i++)
	{
		if (maxX<res[i].position[0])
			maxX=res[i].position[0];
		if (maxY<res[i].position[1])
			maxY=res[i].position[1];
	}

	vector< vector<int> > tab(maxX+1, vector<int> (maxY+1,0));

	for (i=0; i<res.size(); i++)
	{
		tab[res[i].position[0]][res[i].position[1]]=i+1;
	}

	//calcul de tous les carres possibles
	i=0;
	while (i<=maxX)
	{
		itY=0;
		j=0;
		while (j<=maxY)
		{
			for (i=nb_pixels*itX; i<nb_pixels*(itX+1);i++)
			{
				for (j=nb_pixels*itY; j<nb_pixels*(itY+1); j++)
				{
					if (i<=maxX && j<=maxY && tab[i][j])
						feats.push_back(res[tab[i][j]-1]);
				}
			}
			itY++;
			if (!feats.empty()) {
				all_regions_in_image.push_back(Bof());
				all_regions_in_image.back().init_Bof(feats);
            }
			feats.clear();
		}
		itX++;
	}

	cout<<"tous les carres faits"<<endl;



	// calcul de tous les rectangles possibles verticaux
	for (i=0; i<itX; i++)
	{
		for (u=0; u<itY; u++)
		{
			for (j=i*itY+u; j<(i+1)*itY; j++)
			{
				for (k=0; k<all_regions_in_image[j].features.size(); k++)
					feats.push_back(all_regions_in_image[j].features[k]);
				if (j>(i*itY)+u){
					all_regions_in_image.push_back(Bof());
					all_regions_in_image.back().init_Bof(feats);
                }
			}
			feats.clear();
		}
	}

	cout<<"tous les retangles verticaux faits"<<endl;

	// calcul de tous les rectangles possibles horizontaux
	for (j=0; j<itY; j++)
	{
		for (u=0; u<itX; u++)
		{
			for (i=0; i<itX-u; i++)
			{
				for (k=0; k<all_regions_in_image[j+(i+u)*itX].features.size(); k++)
					feats.push_back(all_regions_in_image[j+(i+u)*itX].features[k]);
				if (i>0){
					all_regions_in_image.push_back(Bof());
					all_regions_in_image.back().init_Bof(feats);
                }
			}
			feats.clear();
		}
	}

	cout<<"tous les rectangles horizontaux faits"<<endl;

	//calcul de tous les rectangles possibles horizontaux+verticaux
	for (i=0; i<itX; i++)
	{
		for (u=0; u<itY; u++)
		{
			for (j=i*itX+u+1; j<(i+1)*itX; j++)
			{
				for (v=1; v<itX-i; v++)
				{
					for (w=i*itX+u; w<j+1; w++)
					{
						if (v==1){
							for (k=0; k<all_regions_in_image[w].features.size(); k++)
								feats.push_back(all_regions_in_image[w].features[k]);
                        }
						for (k=0; k<all_regions_in_image[w+v*itX].features.size(); k++)
							feats.push_back(all_regions_in_image[w+v*itX].features[k]);
					}
					all_regions_in_image.push_back(Bof());
					all_regions_in_image.back().init_Bof(feats);
				}
				feats.clear();
			}
		}
	}

	cout<<"rectangles horizontaux+verticaux"<<endl;

}

