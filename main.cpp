#include "main.h"

void testBinary(){
	typedef ft::BinarySearchTree<int, std::less<int> > BinarySearchTree;

	BinarySearchTree tree;

	int arr[] = { 162, 202, 88, 226, 181, 120 ,30, 237, 212, 189, 174, 140, 102, 55, 16 };
	std::srand(std::time(NULL));
	//for (int i = 0; i < 15; ++i)
	//	tree.insert(std::rand() % 100);
	for (int i = 0; i < 5; ++i)
		tree.insert(arr[i]);

	//tree.remove(1520);
	//tree.remove(174);
	//tree.remove(189);


	tree.printTree();
}

void testAVL(){
	typedef ft::AVLTree<int, std::less<int> > AVLTree;

	AVLTree tree;

	int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
	tree.printTree();
	for (int i = 0; i < 16; ++i){
		tree.insert(arr[i]);
		//tree.printTree();
		//cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
	}
	for (int i = 0; i < 16; ++i){
		tree.remove(arr[i]);
		tree.printTree();
		cout << "inserted: " << i << " ** " << arr[i] <<" ------------" << endl;
	}


	/*std::srand(std::time(NULL));
	for (int i = 0; i < 10; ++i)
		tree.insert(std::rand() % 10);*/
	tree.printTree();
}

void readBlackTree(){
	typedef ft::RedBlackTree<int, std::less<int> > RBTree;

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



int main()
{
	//testAVL();
	//testBinary();
	readBlackTree();

	std::map<int, string> h;
	std::map<int, string>::iterator n;


	return (0);
}