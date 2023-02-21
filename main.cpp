/*******************************************/
/*     created by aben-ham 11/6/22         */
/*******************************************/
#include "headers/ft_containers_fox_test/fox.h"


class Tree{
public:
	typedef ft::BinaryNode<std::string> nodeType;
	typedef nodeType* nodePointer;

	enum{
		LEFT, RIGHT
	};

private:
	nodePointer _parent;
public:
	Tree(const std::string& nodeName) : _parent(new nodeType(nodeName)){
	}

	Tree(nodePointer node): _parent(node){}

public:
	int height(nodeType *node) const{
		if (!node)
			return (-1);
		int leftHeight = height(node->leftChild);
		int rightHeight = height(node->rightChild);
		return (std::max(leftHeight, rightHeight) + 1);
	}

	nodePointer addNode(nodePointer node, const std::string &nodeName, int pos){
		nodePointer newNode = new nodeType(nodeName);
		if (pos == LEFT)
			node->leftChild = newNode;
		else
			node->rightChild = newNode;
		return (newNode);
	}

	void	printTree(std::ostream &os = std::cout){
		int h = height(_parent) + 1;
		if (h >= 0)
			_parent->printTree(os, h);
	}

	nodePointer getRoot(){
		return _parent;
	}
};

int main(){
	//mainTests();

	Tree t("|");

	t.addNode(t.getRoot(), "ls", Tree::LEFT);
	Tree::nodePointer node1 = t.addNode(t.getRoot(), "|", Tree::RIGHT);
	t.addNode(node1, "A", Tree::LEFT);
	t.addNode(node1, "B", Tree::RIGHT);

	t.printTree();


	//&|()
	//(ls >& a) '   ' | ls>a || echo "$tt"
	//200002002020000002200000000000
	//[(, c, &, c ,) , c, |,  c, ||, c]
	//[]

	return (0);
}
