#include "main.h"




void	testIterator(){
	typedef ft::RedBlackTree<ft::pair<const int, int>, std::less<int>, std::allocator<ft::pair<const int, int> > > RBTree;
	typedef std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int> > > map_type;
	typedef ft::map<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > my_map;

	int arr[] = {16, 2, 9, 4, 15, 5, 8, 6, 13, 12, 3, 7, 10, 14, 11, 1};


	ft::pair<int, int> map_arr[] = {
			ft::make_pair(16, 4),
			ft::make_pair(2, 4),
			ft::make_pair(9, 5),
			ft::make_pair(4, 5),
			ft::make_pair(15, 5),
			ft::make_pair(8, 5),
			ft::make_pair(6, 5)
	};


	my_map  a(map_arr, map_arr + 3);
	my_map b(a);
	my_map c;
	map_type stdMap;
	c = a;

	a.insert(map_arr + 3, map_arr + 6);
	a.insert(a.begin(), map_arr[6]);
	ft::pair<my_map::iterator, bool> res = a.insert(ft::make_pair(16, 4));
	cout << res.second << endl;
	cout << (*res.first) << endl;
	//stdMap.insert(std::make_pair(25, 77));
	//a.at(2) = 88;
	//a.at(3);
	cout << "A: " << endl;
	a.print();
	cout << "C: " << endl;
	c.print();
	cout << "size of a : " << a.size() << endl;
	cout << "size of b : " << b.size() << endl;
	cout << "size of c : " << c.size() << endl;
	cout << "Is empty : " << a.empty() << endl;
	cout << "Max size : " << a.max_size() << endl;

	a.print();
	for (int i = 0; i < 15; i++){
		my_map::iterator position1 = a.lower_bound(i);
		my_map::iterator position2 = a.upper_bound(i);
		cout << i << "==>" << *position1 << "||" << *position2 << endl;
	}
	//a.print();

	my_map::iterator iter_b, iter_e;

	a.print();
	while (a.size()){
		iter_b = a.begin();
		my_map::value_type data = *iter_b;
		cout << a.size() << " delete: " << data << endl;
		a.erase(iter_b);
		cout << a.size() << " deleted: " << data << endl;
		a.print();
	}
	/*a.print();
	a.erase(2);
	a.print();*/

	/*cout << a.size() << endl;
	a.erase(555);
	cout << a.size() << endl;*/

	/*my_map::iterator iter_b, iter_e;
	iter_b = a.begin();
	iter_e = a.end();
	a.erase(iter_b, iter_e);
	a.print();*/
}


int main()
{

	//testBinary();
	//testAVL();
	//readBlackTree();
	testIterator();

	//std::map<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > b;

	//decltype(i);

	//static_assert(has_member_named_first<ClassB<int> >::value, "MyClass does not have myVariable");

	//std::map

	return (0);
}