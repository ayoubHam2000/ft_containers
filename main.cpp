#include "headers/vector.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include "headers/vector_prelude.h"
#include "headers/test.hpp"
#include <sstream>

#define print_(x) cout << x << endl;
using namespace std;



void test(){
/*

 * */
	int arr[] = {1, 2, 3, 4, 5};
	NAMESPACE::vector<int, track_allocator<int> > b;
	NAMESPACE::vector<int, track_allocator<int> > a;

	a.insert(a.end(), 1);
	a.insert(a.end(), 2);
	a.insert(a.end(), 3);
	a.reserve(1024);
	//a.erase(a.begin() + 1);

	a.assign(arr, arr + 5);



}

void s(){
	int arr[] = {1, 2, 5, 7, 3};
	NAMESPACE::vector<int> a(arr, arr + 5);

	for (NAMESPACE::vector<int>::reverse_iterator crit = a.rbegin(); crit != a.rend(); ++crit) {
		cout << *crit << endl;
	}
}

int main()
{

	test();
	//s();
	//system("leaks ft_containers");
	return (0);
}