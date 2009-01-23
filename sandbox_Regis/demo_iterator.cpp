#include "timer.h"
#include <vector>
#include <iostream>
using namespace std;

#define NDEBUG

template<class T> class Mother{

	public:
		
		Mother(){}
		Mother( const Mother& src ){
			this->_data = src._data;
		}
		Mother( int size ){
			this->_data.resize( size );
		}
		Mother( int size, const T& defVal ){
			this->_data.resize( size, defVal );
		}
		
		inline const T& operator[](const int& i) const {
			return this->_data[i];
		}
		inline T& operator[](const int& i){
			return this->_data[i];
		}
		
		class iterator : public std::iterator<std::forward_iterator_tag, T> {
			public:
				inline iterator(){}
				inline iterator( const typename vector<T>::iterator& it ) : _it(it){}
				inline iterator( const iterator& it ) : _it(it._it){}
				inline ~iterator(){};
				
				inline const iterator& operator=( const iterator& it ){
					this->_it = it._it;
					return *this;
				}
				
				inline bool operator==( const iterator& it ){
					return this->_it == it._it;
				}
				
				inline bool operator!=( const iterator& it ){
					return !(*this == it);
				}
				
				inline iterator& operator++(){
					this->_it++;
					return *this;
				}
				inline iterator& operator++(int){
					++(this->_it);
					return *this;
				}
				inline T& operator*(){
					return *(this->_it);
				}
				
				
			protected:
				typename vector<T>::iterator _it;
		};
		
		inline iterator begin(){
			return iterator( this->_data.begin() );
		}
				
		inline iterator end(){
			return iterator( this->_data.end() );
		}

	protected:
		vector<T> _data;
};

int main()
{
	int size = 100000000;
	int index;
	float sum;
	timer t;
	typedef double EltType;
	Mother<EltType> x(size);
	
	t.start();
	index = 0;
	sum = 0;
	for( int i = 0; i < size; i++, index++ )
	{
		x[i] = index;
		sum += x[i];
	}
	cout << t.elapsed_time() << "s without iterator" << endl;
	
	t.restart();
	index = 0;
	sum = 0;
	for( Mother<EltType>::iterator it = x.begin(); it != x.end(); it++, index++ )
	{
		*it = index;
		sum += *it;
	}
	cout << t.elapsed_time() << "s with iterator" << endl;
	
// 	for( Mother<EltType>::iterator it = x.begin(); it != x.end(); it++ )
// 		cout << *it << endl;
}
