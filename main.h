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
#include <chrono>
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

	static void print(){
		cout << "nb_construct = " << A::nb_construct << endl;
		cout << "nb_copy_construct = " << A::nb_copy_construct << endl;
		cout << "nb_assigned = " << A::nb_assigned << endl;
		cout << "nb_delete = " << A::nb_delete << endl;
	}

	static void reset(){
		A::nb_assigned = 0;
		A::nb_delete = 0;
		A::nb_copy_construct = 0;
		A::nb_construct = 0;
	}
};

struct MyTimer{
	typedef std::chrono::high_resolution_clock::time_point time_type;

	time_type s;

	MyTimer(){
		s = std::chrono::high_resolution_clock::now();
	}

	void reset(){
		s = std::chrono::high_resolution_clock::now();
	}

	void print_ms(){
		time_type end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - s).count() / 1000000 << "ms\n";
	}

	void print_us(){
		time_type end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - s).count() / 1000 << "ms\n";
	}
};


void vector_test()
{
	int max = 10000;
	{

		std::vector<int, track_allocator<int> > v;

		for (int i = 0; i < max; i++) {
			v.push_back(i);
		}
		MyTimer timer;
		while (!v.empty())
			v.erase(v.begin());

		timer.print_ms();

		track_allocator<int>::print();
		//A::print();
	}

	track_allocator<int>::reset();
	A::reset();

	{

		ft::vector<int, track_allocator<int> > v;

		for (int i = 0; i < max; i++) {
			v.push_back(i);
		}
		MyTimer timer;
		while (!v.empty()) {
			v.erase(v.begin());
		}

		timer.print_ms();

		track_allocator<int>::print();
		//A::print();
	}
}

long long A::nb_assigned = 0;
long long A::nb_delete = 0;
long long A::nb_construct = 0;
long long A::nb_copy_construct = 0;


#endif //FT_CONTAINERS_MAIN_H
