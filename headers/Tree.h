/*******************************************/
/*     created by aben-ham 11/21/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TREE_H
#define FT_CONTAINERS_TREE_H

#include <iostream>
#include "queue.h"

//TODO Deep Copy
namespace ft{

template <class T>
struct BinaryNode
{
public:
	typedef T		value_type;
public:
	value_type		data;
	BinaryNode		*leftChild;
	BinaryNode		*rightChild;

	BinaryNode() : data(), leftChild(nullptr), rightChild(nullptr){}

	BinaryNode(const value_type &data, BinaryNode *leftChild = nullptr, BinaryNode *rightChild = nullptr) :
			data(data), leftChild(leftChild), rightChild(rightChild){}

	BinaryNode(const BinaryNode &other) : data(other.data), leftChild(other.leftChild), rightChild(other.rightChild){}

	virtual ~BinaryNode(){}
	BinaryNode &operator=(const BinaryNode &other){
		data = other.data;
		leftChild = (other.leftChild);
		rightChild = (other.rightChild);
		return (*this);
	}
};

template <
        class T,
		class Compare,
		class Allocator = std::allocator<T>(),
		class NodeAllocator = std::allocator<BinaryNode<T> > >
class BinaryTree{

#pragma region BinaryTree
public:
	typedef T                                      						value_type;
	typedef Compare                                 					value_compare;
	typedef Allocator                               					allocator_type;
	typedef NodeAllocator                               				node_allocator_type;

	typedef typename allocator_type::size_type							size_type;

	typedef BinaryNode<T>												BinaryNode;
	typedef BinaryNode *												BinaryNodePointer;
protected:
	BinaryNodePointer													_parent;
	node_allocator_type													_node_alloc;

public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	BinaryTree() : _parent(nullptr), _node_alloc() {}
	BinaryTree(const BinaryTree &other) : _parent(clone(other._parent)), _node_alloc() {}

	BinaryTree &operator=(const BinaryTree &other){
		BinaryTree	tmp(other);
		destroyTree(_parent);
		this->_parent = tmp._parent;
		this->_node_alloc = _node_alloc;
		return (*this);
	}

	virtual ~BinaryTree(){
		destroyTree(_parent);
	}

	BinaryNodePointer clone(BinaryNodePointer node){
		if (!node)
			return (nullptr);
		BinaryNodePointer tmp = _node_alloc.allocate(1);
		_node_alloc.construct(
				tmp,
				BinaryNode(node->data, clone(node->leftChild), clone(node->rightChild))
			);
		return (tmp);
	}

	void	destroyTree(BinaryNodePointer &node){
		if (node){
			destroyTree(node->leftChild);
			destroyTree(node->rightChild);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			node = nullptr;
		}
	}

	size_type height(BinaryNode *node){
		if (node){
			size_type heightOfTheLeft = height(node->leftChild);
			size_type heightOfTheRight = height(node->rightChild);
			return std::max(heightOfTheLeft, heightOfTheRight) + 1;
		}
		return (0);
	}
	size_type height(){
		return height(_parent);
	}

	//╭──┴──╮
	/*
	 *    6
	 * ╭──┴──╮
	 * 7     8
	 */

	void	print_center(std::ostream &os, const std::string &item, size_type buffer_size){
		int i = 0;
		size_type nb = buffer_size - item.size();
		while (i < nb / 2){
			os << ' ';
			i++;
		}
		os << item;
		while (i < nb){
			os << ' ';
			i++;
		}
	}

	void 	printTree(BinaryNode *node, std::ostream &os, size_t buffer_size){
		size_type word_size = 4;
		size_type level = 1;
		size_type s = (buffer_size - word_size * level) / (level + 1);
		size_type level_item = 1;
		size_type type = 1;

		ft::queue<BinaryNodePointer> queue;
		queue.enqueue(node);
		while (!queue.empty()){
			if (type == 1){
				BinaryNodePointer item = queue.dequeue();
				if (item){
					print_center(os, std::to_string(item->data), buffer_size);
					queue.enqueue(item->leftChild);
					queue.enqueue(item->rightChild);
				}else{
					print_center(os, "?", buffer_size);
				}
				level_item--;
				if (level_item == 0){
					type = 1;
					level *= 2;
					level_item = level;
					s = (buffer_size - word_size * level) / (level + 1);
					os << "\n";
				}
			}
		}
	}

	void printTree(std::ostream &os = std::cout){
		int depth = 5;
		size_type n = 1;
		while (depth--){
			n *= 2;
		}
		n = 4 * n + (n + 1) * 2;
		printTree(_parent, os, n);
	}

#pragma endregion

}; //End BinaryClass

//==================================================================

template <
        class T,
		class Compare,
		class Allocator = std::allocator<T>,
		class NodeAllocator = std::allocator<BinaryNode<T> > >
class BinarySearchTree: public BinaryTree<T, Compare, Allocator, NodeAllocator>{

#pragma region BinarySearchTree
private:
	typedef BinaryTree<T, Compare, Allocator>				_base;
protected:
	typedef typename _base::BinaryNode						BinaryNode;
	typedef  BinaryNode	*									NodePointer;
public:
	typedef typename _base::value_type                      value_type;
	typedef typename _base::value_compare                   value_compare;
	typedef typename _base::allocator_type                  allocator_type;

	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;

public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	BinarySearchTree() : _base() {}
	BinarySearchTree(const BinarySearchTree &other) : _base(other) {}
	BinarySearchTree &operator=(const BinarySearchTree &other){
		_base::operator=(other);
		return (*this);
	}
	~BinarySearchTree(){}

#pragma endregion

#pragma region utils
	/*****************************************************************/
	// Utils (findMin, findMax, contains)
	/*****************************************************************/

	NodePointer findMin(NodePointer root){
		if (!root)
			return (nullptr);
		if (root->leftChild == nullptr)
			return (root);
		return findMin(root->leftChild);
	}

	NodePointer findMax(NodePointer root){
		if (!root)
			return (nullptr);
		if (root->rightChild == nullptr)
			return (root);
		return (findMax(root->rightChild));
	}

	bool contains(NodePointer root, const_reference value){
		if (!root)
			return (false);
		if (root->data < value)
			return (contains(root->rightChild, value));
		if (value < root->data)
			return (contains(root->leftChild, value));
		return (true);
	}

	void insert(const_reference value){
		insert(this->_parent, value);
	}

	void insert(NodePointer &root, const_reference value){
		if (root == nullptr){
			NodePointer new_element = this->_node_alloc.allocate(1, nullptr);
			this->_node_alloc.construct(new_element, BinaryNode(value));
			root = new_element;
		}
		else if (root->data < value){
			insert(root->rightChild, value);
		}
		else if (value < root->data){
			insert(root->leftChild, value);
		}
		//Todo: Duplicate element
	}

	void remove(NodePointer &root, const_reference value){
		if (!root)
			return ;
		if (root->data < value){
			remove(root->rightChild, value);
		} else if (value < root->data){
			remove(root->leftChild, value);
		} else if (root->leftChild && root->rightChild){
			NodePointer minRightTree = findMin(root->rightChild);
			root->data = minRightTree->data;
			if (minRightTree->rightChild){
				NodePointer tmp = minRightTree->rightChild;
				*minRightTree = *tmp;
				this->_node_alloc.destroy(tmp);
				this->_node_alloc.deallocate(tmp, 1);
			}
		} else if (root->leftChild || root->rightChild){
			NodePointer tmp = (root->leftChild != nullptr) ? root->leftChild : root->rightChild;
			*root = *tmp;
			this->_node_alloc.destroy(tmp);
			this->_node_alloc.deallocate(tmp, 1);
		} else {
			this->_node_alloc.destroy(root);
			this->_node_alloc.deallocate(root, 1);
			root = nullptr;
		}
	}

#pragma endregion
};

template <class T, class Compare, class Allocator>
class RedBlackTree : public BinaryTree<T, Compare, Allocator>{
private:
	typedef BinaryTree<T, Compare, Allocator>	_base;
	typedef typename _base::BinaryNode			BinaryNode;
public:
	typedef T                                   value_type;
	typedef Compare                             value_compare;
	typedef Allocator                           allocator_type;

	struct Node : BinaryNode {
		bool	color; //false RED, True Black

		enum {RED, BLACK};
		Node() : color(RED), BinaryNode(){}
		~Node(){}
		Node(const Node &other) : color(other.color), BinaryNode(other){}
		Node &operator=(const Node &other){
			color = other.color;
			BinaryNode::operator=(other);
			return (*this);
		}
		void flipColor(){color = !color;}
	};
};


} //End NameSpace

#endif //FT_CONTAINERS_TREE_H
