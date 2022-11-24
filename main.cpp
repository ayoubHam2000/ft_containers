#include "main.h"


int main()
{
	typedef ft::BinarySearchTree<int, std::less<int> > BinarySearchTree;

	BinarySearchTree tree;

	map<int, std::less<int> >::iterator f;
	int arr[] = {162, 202, 88, 226, 181, 120 ,30, 237, 212, 189, 174, 140, 102, 55, 16 };
	for (int i = 0; i < 15; ++i)
		tree.insert(arr[i]);
	tree.printTree();

	return (0);
}