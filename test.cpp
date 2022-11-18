/*******************************************/
/*     created by aben-ham 11/9/22         */
/*******************************************/


#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <algorithm>

#include "headers/iterator.hpp"
#include "headers/vector.hpp"
#include "headers/algorithm.hpp"

using namespace std;

void	all_vector(){
	ft::vector<int> a;
	ft::vector<int> b(a);
	ft::vector<int> c(a.begin(), a.end());
	ft::vector<int> d(10);
	ft::vector<int> e(10, 10);

	a.insert(a.begin(), 20);
	a.insert(a.begin(), 10, 50);
	a.insert(a.begin(), a.begin(), a.end());
	a.erase(a.begin());
	a.erase(a.begin(), a.begin());
	a.assign(a.begin(), a.begin());
	a.assign(10, 20);

	a.push_back(50);
	a.pop_back();
	a.swap(a);
	a.clear();

	a.size();
	a.capacity();
	a.max_size();
	a.resize(50);
	a.resize(50, 30);
	a.empty();
	a.reserve(10);
	a.shrink_to_fit();


	a.begin();
	a.end();
	a.rbegin();
	a.rend();
	a.cbegin();
	a.cend();
	a.crbegin();
	a.crend();

	a[10];
	a.at(20);
	a.front();
	a.back();
	a.data();
	a.get_allocator();

	bool t;
	t = a == b;
	t = a != b;
	t = a < b;
	t = a <= b;
	t = a > b;
	t = a >= b;
	swap(a, b);
}

