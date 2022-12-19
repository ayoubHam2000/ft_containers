/*******************************************/
/*     created by aben-ham 11/11/22         */
/*******************************************/

void testBinary(){
	typedef ft::BinarySearchTree<int, std::less<int>, std::allocator<int> > BinarySearchTree;

	BinarySearchTree tree;



	{
		int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
		tree.printTree();
		int meddle = 8;
		for (int i = 0; i < meddle; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < 16; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}


	{
		int arr[] = {16, 2, 9, 4, 15, 5, 8, 6, 13, 12, 3, 7, 10, 14, 11, 1};
		int size = sizeof(arr) / sizeof(int);
		tree.printTree();
		int meddle = 1;
		for (int i = 0; i < meddle; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "deleted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < size; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "deleted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}


}

void testAVL(){
	typedef ft::AVLTree<int, std::less<int>, std::allocator<int> > AVLTree;

	AVLTree tree;

	{
		int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
		tree.printTree();
		int meddle = 8;
		for (int i = 0; i < meddle; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < 16; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}


	AVLTree::iterator s = tree.begin();
	AVLTree::iterator e = tree.end();
	while (s != e){
		tree.remove(*s);
		++s;
	}

	{
		int arr[] = {16, 2, 9, 4, 15, 5, 8, 6, 13, 12, 3, 7, 10, 14, 11, 1};
		int size = sizeof(arr) / sizeof(int);
		tree.printTree();
		int meddle = 2;
		for (int i = 0; i < meddle; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "deleted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < size; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "deleted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}
}

void readBlackTree(){
	typedef ft::RedBlackTree<int, std::less<int>, std::allocator<int> > RBTree;

	RBTree tree;

	{
		int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
		tree.printTree();
		int meddle = 8;
		for (int i = 0; i < meddle; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < 16; ++i){
			tree.insert(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}

	RBTree::iterator s = tree.begin();
	RBTree::iterator e = tree.end();
	while (s != e){
		tree.remove(*s);
		++s;
	}

	{
		int arr[] = {16, 2, 9, 4, 15, 5, 8, 6, 13, 12, 3, 7, 10, 14, 11, 1};
		int size = sizeof(arr) / sizeof(int);
		tree.printTree();
		int meddle = 1;
		for (int i = 0; i < meddle; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
		for (int i = meddle; i < size; ++i){
			tree.remove(arr[i]);
			tree.printTree();
			cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
		}
	}


}













/*
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



}
*/

#define NS std

/*
void testErase(){
	typedef ft::RedBlackTree<ft::pair<const int, int>, std::less<int>, std::allocator<ft::pair<const int, int> > > RBTree;
	typedef std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int> > > map_type;
	typedef std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int> > > my_map;
	//typedef ft::map<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > my_map;

	int arr[] = {16, 2, 9, 4, 15, 5, 8, 6, 13, 12, 3, 7, 10, 14, 11, 1};


	NS::pair<int, int> map_arr[] = {
			NS::make_pair(16, 4),
			NS::make_pair(2, 4),
			NS::make_pair(9, 5),
			NS::make_pair(4, 5),
			NS::make_pair(15, 5),
			NS::make_pair(8, 5),
			NS::make_pair(6, 5)
	};


	my_map::iterator iter_b, iter_e;
	my_map  a(map_arr, map_arr + 6);
	//a.print();

	iter_b = a.begin();
	iter_e = a.end();

	iter_b = a.find(4);
	a.erase(4);
	cout << iter_b->first << endl;
	for (my_map::iterator i = iter_b; i != iter_e; ++i){
		my_map::value_type data = *i;
		cout << a.size() << " delete: " << data << endl;
		a.erase(i);
		cout << a.size() << " deleted: " << data << endl;
		a.print();
	}

}
*/