/*******************************************/
/*     created by aben-ham 11/23/22         */
/*******************************************/

#ifndef FT_CONTAINERS_MAIN_H
#define FT_CONTAINERS_MAIN_H

#include "headers/vector.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <stdlib.h>
//#include "headers/vector_prelude.h"
#include "headers/vector_prelude_ben.h"
#include "headers/test.hpp"
#include <stack>
#include <sstream>
#include <map>
#include <set>
#include "headers/Tree.h"

#define print_(x) cout << x << endl;
using namespace std;

template <class T, class Alloc>
ostream &operator<<(ostream &os, NAMESPACE::vector<T, Alloc> &a){
	for (typename NAMESPACE::vector<T, Alloc>::iterator it = a.begin(); it != a.end(); ++it){
		os << *it << ", ";
	}
	return os;
}



class A{
public:
	static long long nb_assigned;
	static long long nb_delete;
	static long long nb_construct;
	static long long nb_copy_construct;

	int i;
	A(): i(0){
		nb_construct++;
	}

	~A(){
		nb_delete++;
	}

	A(const A &obj): i(obj.i){
		nb_copy_construct++;
	}

	A &operator=(const A &obj){
		i = obj.i;
		nb_delete++;

		return (*this);
	}
};

long long A::nb_assigned = 0;
long long A::nb_delete = 0;
long long A::nb_construct = 0;
long long A::nb_copy_construct = 0;


#endif //FT_CONTAINERS_MAIN_H
