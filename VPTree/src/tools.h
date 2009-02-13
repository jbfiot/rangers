#ifndef TOOLS_H
#define TOOLS_H


#include <sstream>
#include <string>

using namespace std;
// Pas de namespace dans les fichiers header
// Here is why you should never write using declarations in header files at all, not even in a namespace scope: 
// The meaning of the using declaration may change depending on what other headers happen to be #included before it in any given module. 
// http://www.gotw.ca/publications/migrating_to_namespaces.htm

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
