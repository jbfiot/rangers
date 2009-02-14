#ifndef TOOLS_H
#define TOOLS_H

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


#endif
