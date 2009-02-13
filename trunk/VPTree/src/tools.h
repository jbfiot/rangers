#ifndef TOOLS_H
#define TOOLS_H


#include <sstream>
#include <string>

using namespace std;

int *get_random_set_indexes(int k,int n);

template <class T>
inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

double strtodouble(const string &what);


#endif
