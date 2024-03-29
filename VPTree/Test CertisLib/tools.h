#ifndef TOOLS_H
#define TOOLS_H

#include "feature.h"
#include "bof.h"
#include "vector.h"

#include <sstream>
#include <string>
#include <vector>

void get_random_set_indexes(int k,int n, std::vector<int> &indexes);

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

double strtodouble(const std::string &what);

void get_all_regions_subsets( const std::vector<Feature>& res, std::vector<Bof>& all_regions_in_image, int nb_pixels,
							 int index);

#endif
