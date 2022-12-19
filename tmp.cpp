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