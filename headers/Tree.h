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
	BinaryNode		*parent;
	int 			height;
	int 			color; //0 red, 1 black

	enum COLOR{
		RED, BLACK
	};

	BinaryNode() : data(), leftChild(nullptr), rightChild(nullptr),parent(nullptr), height(0), color(RED){}

	BinaryNode(const value_type &data, BinaryNode *parent = nullptr, BinaryNode *leftChild = nullptr, BinaryNode *rightChild = nullptr) :
			data(data),
			leftChild(leftChild),
			rightChild(rightChild),
			parent(parent),
			height(0),
			color(RED)
			{}

	BinaryNode(const BinaryNode &other) :
			data(other.data),
			leftChild(other.leftChild),
			rightChild(other.rightChild),
			parent(other.parent),
			height(0),
			color(RED)
			{}

	virtual ~BinaryNode(){}
	BinaryNode &operator=(const BinaryNode &other){
		data = other.data;
		leftChild = (other.leftChild);
		rightChild = (other.rightChild);
		parent = (other.parent);
		height = other.height;
		color = other.color;
		return (*this);
	}

	void flipColor(){
		color = !this->color;
	}

	BinaryNode *getGrandParent(){
		if (parent)
			return (parent->parent);
		return (nullptr);
	}

	BinaryNode *getUncle(){
		if (parent && parent->parent){
			if (parent->parent->leftChild == parent)
				return (parent->parent->rightChild);
			else
				return (parent->parent->leftChild);
		}
		return (nullptr);
	}

	//pre-condition parent must exist
	BinaryNode *&getRef(){
		return (this->parent->leftChild == this ? this->parent->leftChild : this->parent->rightChild);
	}

	BinaryNode *&getRef(BinaryNode *&root){
		return (this->parent == nullptr ? root : getRef());
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

	virtual int height(BinaryNode *node) const{
		if (!node)
			return (-1);
		int leftHeight = height(node->leftChild);
		int rightHeight = height(node->rightChild);
		return (std::max(leftHeight, rightHeight) + 1);
	}

	int height(){
		return height(_parent);
	}

	void	print_center(std::ostream &os, const std::string &item, size_type buffer_size, int color){
		if (color == BinaryNode::RED)
			os << "\033[1;31m";
		int i = 0;
		if (item.size() > buffer_size){
			os << item.substr(0, buffer_size - 1);
			os << '.';
		}else{
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
		if (color == BinaryNode::RED)
			os << "\033[0m";
	}

	void 	print_r(std::ostream &os, size_type buffer_size){
		int i = 0;
		size_type nb = buffer_size / 4;
		while (i < nb){
			os << ' ';
			i++;
		}
		os << "╭";
		i++;
		while (i + nb + 2 < buffer_size){
			if (i == (buffer_size - 1) / 2)
				os << "┴";
			else
				os << "─";
			i++;
		}
		os << "╮";
		i++;
		while (i < buffer_size){
			os << ' ';
			i++;
		}
	}

	void 	printTree(BinaryNode *node, std::ostream &os, size_t tree_height){
		size_type level_item = tree_height;
		size_type buffer_size = 1;
		while (level_item--){
			buffer_size *= 2;
		}
		buffer_size = 2 * buffer_size;

		size_type level = 1;
		size_type depth = 0;
		size_type type = 1;
		level_item = 1;

		ft::queue<BinaryNodePointer> queue;
		ft::queue<bool> is_empty_node;
		queue.enqueue(node);
		while (depth < tree_height){
			if (type == 1){
				BinaryNodePointer item = queue.dequeue();
				if (item){
					print_center(os, std::to_string(item->data), buffer_size, item->color);
					queue.enqueue(item->leftChild);
					queue.enqueue(item->rightChild);
					is_empty_node.enqueue(true);
				}else{
					queue.enqueue(nullptr);
					queue.enqueue(nullptr);
					print_center(os, " ", buffer_size, BinaryNode::BLACK); //"?" to show deleted item
					is_empty_node.enqueue(false); //false for turn of branch drawing
				}
				level_item--;
				if (level_item == 0){
					type = 2;
					level_item = level;
					level *= 2;
					depth++;
					os << "\n";
				}
			} else {
				while (level_item--){
					bool val = is_empty_node.dequeue();
					if (val)
						print_r(os, buffer_size);
					else
						print_center(os, " ", buffer_size, BinaryNode::BLACK);
				}
				level_item = level;
				type = 1;
				buffer_size /= 2;
				os << "\n";
			}
		}
	}

	void printTree(std::ostream &os = std::cout){
		int h = height() + 1;
		if (h >= 0)
			printTree(_parent, os, h);
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
	typedef BinaryTree<T, Compare, Allocator, NodeAllocator>	_base;
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
	virtual ~BinarySearchTree(){}

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
		insertInto(this->_parent, value);
	}

	virtual void balance(NodePointer &node){}

	NodePointer	constructNode(const_reference value, NodePointer parent = nullptr){
		NodePointer node = this->_node_alloc.allocate(1, nullptr);
		this->_node_alloc.construct(node, BinaryNode(value, parent));
		return (node);
	}

	void deleteNode(NodePointer node){
		this->_node_alloc.destroy(node);
		this->_node_alloc.deallocate(node, 1);
	}

	virtual void insertInto(NodePointer &root, const_reference value){
		if (root == nullptr){
			root = constructNode(value);
		}
		else if (root->data < value){
			insertInto(root->rightChild, value);
		}
		else if (value < root->data){
			insertInto(root->leftChild, value);
		}
		//Todo: Duplicate element
		balance(root);
	}

	NodePointer getParent(NodePointer root, NodePointer node){
		if (!root || !node || root == node)
			return (nullptr);
		if (root->rightChild == node || root->leftChild == node)
			return (root);
		if (root->data < node->data)
			getParent(root->rightChild, node);
		if (node->data < root->data)
			getParent(root->leftChild, node);
	}

	virtual void removeFrom(NodePointer &root, const_reference value){
		if (!root)
			return ;
		if (root->data < value){
			removeFrom(root->rightChild, value);
		} else if (value < root->data){
			removeFrom(root->leftChild, value);
		} else if (root->leftChild && root->rightChild){
			NodePointer minRightTree = findMin(root->rightChild);
			root->data = minRightTree->data;
			removeFrom(root->rightChild, minRightTree->data);
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

		balance(root);
	}

	void remove(const_reference value){
		this->removeFrom(this->_parent, value);
	}

#pragma endregion
};

template <
        class T,
		class Compare,
		class Allocator = std::allocator<T>,
		class NodeAllocator = std::allocator<BinaryNode<T> > >
class AVLTree : public BinarySearchTree<T, Compare, Allocator, NodeAllocator>
{
#pragma region AVLTree
private:
	typedef BinarySearchTree<T, Compare, Allocator, NodeAllocator>	_base;
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

	AVLTree() : _base() {}
	AVLTree(const AVLTree &other) : _base(other) {}
	AVLTree &operator=(const AVLTree &other){
		_base::operator=(other);
		return (*this);
	}
	~AVLTree(){}

#pragma endregion //AVLTree

#pragma region utils

	virtual int height(BinaryNode *node) const{
		return ((node == nullptr) ? -1 : node->height);
	}

	/**
	 * @details
	 *	  n2             n1
	 *	╭──┴──╮        ╭──┴──╮
	 *  n1    z   *->  x     n2
	 * ╭┴╮                  ╭┴╮
	 * x y                  y z
	 */
	void singleRotationLeftToRight(NodePointer &n2){
		NodePointer n1 = n2->leftChild;
		n2->leftChild = n1->rightChild;
		n1->rightChild = n2;
		n2->height = std::max(this->height(n2->leftChild), this->height(n2->rightChild)) + 1;
		n1->height = std::max(this->height(n1->leftChild), n2->height) + 1;
		n2 = n1;
	}

	/**
	 * @details
	 *	  n2             n1
	 *	╭──┴──╮        ╭──┴──╮
	 *  n1    z   <-*  x     n2
	 * ╭┴╮                  ╭┴╮
	 * x y                  y z
	 */
	void singleRotationRightToLeft(NodePointer &n1){
		NodePointer n2 = n1->rightChild;
		n1->rightChild = n2->leftChild;
		n2->leftChild = n1;
		n1->height = std::max(this->height(n1->leftChild), this->height(n1->rightChild)) + 1;
		n2->height = std::max(n1->height, this->height(n2->rightChild)) + 1;
		n1 = n2;
	}

	/**
	 * @details
	 *	  n3                 n2
	 *	╭──┴──╮           ╭───┴───╮
	 *  n1    D           n1      n3
	 * ╭─┴─╮      *->   ╭─┴─╮    ╭─┴─╮
	 * A   n2           A   B    C   D
	 *   ╭──┴──╮
	 *   B     C
	 */
	void doubleRotationLeftRight(NodePointer &n3){
		singleRotationRightToLeft(n3->leftChild);
		singleRotationLeftToRight(n3);
	}

	/**
	* @details
	*	  n1                  n2
	*	╭──┴──╮            ╭───┴───╮
	*   A     n3          n1       n3
	*       ╭─┴─╮  *->   ╭─┴─╮    ╭─┴─╮
	*       n2  D        A   B    C   D
	*    ╭──┴──╮
	*    B     C
	*/
	void doubleRotationRightLeft(NodePointer &n1){
		singleRotationLeftToRight(n1->rightChild);
		singleRotationRightToLeft(n1);
	}

	virtual void balance(NodePointer &node){
		if (node == nullptr)
			return ;
		int balance = this->height(node->leftChild) - this->height(node->rightChild);
		if (balance > 1){
			if (this->height(node->leftChild->leftChild) >= this->height(node->leftChild->rightChild))
				singleRotationLeftToRight(node);
			else
				doubleRotationLeftRight(node);
		}else if (balance < -1){
			if (this->height(node->rightChild->rightChild) >= this->height(node->rightChild->leftChild))
				singleRotationRightToLeft(node);
			else
				doubleRotationRightLeft(node);
		}
		node->height = std::max(this->height(node->leftChild), this->height(node->rightChild)) + 1;
	}

#pragma endregion //utils

}; //EndAVLTree

template <
		class T,
		class Compare,
		class Allocator = std::allocator<T>,
		class NodeAllocator = std::allocator<BinaryNode<T> > >
class RedBlackTree : public BinarySearchTree<T, Compare, Allocator, NodeAllocator>{
private:
	typedef BinarySearchTree<T, Compare, Allocator, NodeAllocator>	_base;
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

	RedBlackTree() : _base() {}
	RedBlackTree(const RedBlackTree(&other)) : _base(other) {}
	RedBlackTree &operator=(const RedBlackTree(&other)){
		_base::operator=(other);
		return (*this);
	}
	~RedBlackTree(){}

#pragma endregion //RedBlackTree

#pragma region utils

	/**
	 * @details
	 *	  n2             n1
	 *	╭──┴──╮        ╭──┴──╮
	 *  n1    z   *->  x     n2
	 * ╭┴╮                  ╭┴╮
	 * x y                  y z
	 */
	void singleRotationLeftToRight(NodePointer &n2){
		NodePointer n1 = n2->leftChild;
		NodePointer y = n1->rightChild;
		n1->parent = n2->parent;
		n2->parent = n2->leftChild;
		if (y)
			y->parent = n2;
		n2->leftChild = y;
		n1->rightChild = n2;
		n2->height = std::max(this->height(n2->leftChild), this->height(n2->rightChild)) + 1;
		n1->height = std::max(this->height(n1->leftChild), n2->height) + 1;
		n2 = n1;
	}

	/**
	 * @details
	 *	  n2             n1
	 *	╭──┴──╮        ╭──┴──╮
	 *  n1    z   <-*  x     n2
	 * ╭┴╮                  ╭┴╮
	 * x y                  y z
	 */
	void singleRotationRightToLeft(NodePointer &n1){
		NodePointer n2 = n1->rightChild;
		NodePointer y = n2->leftChild;
		n2->parent = n1->parent;
		n1->parent = n1->rightChild;
		if (y)
			y->parent = n1;
		n1->rightChild = y;
		n2->leftChild = n1;
		n1->height = std::max(this->height(n1->leftChild), this->height(n1->rightChild)) + 1;
		n2->height = std::max(n1->height, this->height(n2->rightChild)) + 1;
		n1 = n2;
	}

	/**
	 * @details
	 *	  n3                 n2
	 *	╭──┴──╮           ╭───┴───╮
	 *  n1    D           n1      n3
	 * ╭─┴─╮      *->   ╭─┴─╮    ╭─┴─╮
	 * A   n2           A   B    C   D
	 *   ╭──┴──╮
	 *   B     C
	 */
	void doubleRotationLeftRight(NodePointer &n3){
		singleRotationRightToLeft(n3->leftChild);
		singleRotationLeftToRight(n3);
	}

	/**
	* @details
	*	  n1                  n2
	*	╭──┴──╮            ╭───┴───╮
	*   A     n3          n1       n3
	*       ╭─┴─╮  *->   ╭─┴─╮    ╭─┴─╮
	*       n2  D        A   B    C   D
	*    ╭──┴──╮
	*    B     C
	*/
	void doubleRotationRightLeft(NodePointer &n1){
		singleRotationLeftToRight(n1->rightChild);
		singleRotationRightToLeft(n1);
	}

	virtual void insertInto(NodePointer &root, const_reference value){
		NodePointer node = root;
		NodePointer parent = nullptr;
		while (node){
			parent = node;
			if (node->data < value)
				node = node->rightChild;
			else if (value < node->data)
				node = node->leftChild;
			else
				return ;
		}
		node = this->constructNode(value, parent);
		if (!parent){
			root = node;
			root->color = BinaryNode::BLACK;
		}
		else{
			if (node->data < parent->data)
				parent->leftChild = node;
			else
				parent->rightChild = node;
			fixUpRedBlackTree(root, node);
		}
	}

	void fixUpRedBlackTree(NodePointer &root, NodePointer node){
		while (node != root && node->parent->color == BinaryNode::RED){
			NodePointer grandParent = node->getGrandParent();
			if (grandParent){
				NodePointer parent = node->parent;
				NodePointer uncle = node->getUncle();
				if (!uncle || uncle->color == BinaryNode::BLACK){
					NodePointer &r = (grandParent == root) ? root : grandParent->getRef();
					if (grandParent->leftChild == parent && parent->leftChild == node){
						singleRotationLeftToRight(r);
					} else if (grandParent->rightChild == parent && parent->rightChild == node){
						singleRotationRightToLeft(r);
					} else if (grandParent->leftChild == parent && parent->rightChild == node){
						doubleRotationLeftRight(r);
					} else{
						doubleRotationRightLeft(r);
					}
					r->color = BinaryNode::BLACK;
					r->rightChild->color = BinaryNode::RED;
					r->leftChild->color = BinaryNode::RED;
					break ;
				} else {
					if (grandParent != root)
						grandParent->color = BinaryNode::RED;
					uncle->color = BinaryNode::BLACK;
					parent->color = BinaryNode::BLACK;
					node = grandParent;
				}
			}
		}
	}

	/**
	 * @note
	 * pre-condition: a can't be null, b can take the value null
	 * replace a with b
	 */
	void	Transplant(NodePointer a, NodePointer b){
		if (!a->parent)
			this->_parent = b;
		else if (a->parent->leftChild == a)
			a->parent->leftChild = b;
		else
			a->parent->rightChild = b;
		if (b)
			b->parent = a->parent;
	}

	/**
	 * @var node is the node that will be delete that take the value of @param value
	 * @var y is the node that will replace node in case node hase two children, other wise y = node
	 * @var x is the node (or null) that will take the y's color (it will have two colors: itself and y's color)
	 * @var oldColor will save the y's color
	 * @node if y's oldColor is black that will result of deletion of a black node
	 */
	void	removeFrom(NodePointer &root, const_reference value){
		NodePointer node = root;
		NodePointer x;
		NodePointer y;
		NodePointer xParent;
		int 		isLeftChild;
		int 		oldColor;

		while (node){
			if (value < node->data)
				node = node->leftChild;
			else if (value > node->data)
				node = node->rightChild;
			else
				break ;
		}
		if (node){
			oldColor = node->color;
			if (!node->leftChild){
				x = node->rightChild;
				Transplant(node, node->rightChild);
				xParent = node->parent;
				isLeftChild = 0;
			}else if (!node->rightChild){
				x = node->leftChild;
				Transplant(node, node->leftChild);
				xParent = node->parent;
				isLeftChild = 1;
			}else{
				y = this->findMin(node->rightChild);
				oldColor = y->color;
				x = y->rightChild;
				xParent = y;
				isLeftChild = 0;
				if (node->rightChild != y){
					Transplant(y, x);
					xParent = y->parent;
					isLeftChild = 1;
					y->rightChild = node->rightChild;
					y->rightChild->parent = y;
				}
				Transplant(node, y);
				y->leftChild = node->leftChild;
				y->leftChild->parent = y;
				y->color = node->color;
			}
			this->deleteNode(node);
			if (oldColor == BinaryNode::BLACK)
				removeFexUp(x, xParent, isLeftChild);
		}
	}

	/**
	 * @details
	 *  x will be (doubly black) or (red and black)
	 *  case 1 x's sibling w is red (the parent and the children of w will black)
	 *  -> right rotation of the parent case that x sibling will be black
	 *  case 2 x's sibling w is black and w's children are black
	 *  -> still w's black color (w will be red) in favorite of the parent (parent will be x)
	 *  case 3 x's sibling w is black and, w’s left child is red, and w’s right child is black
	 *  -> left rotation on w => w will be w's left child that will take black color and have right child of red color
	 *  case 4 x's sibling w is black and have red right child
	 *  -> right rotation on w.p => the extra black of x will be transfer to w.p (end of loop)
	 *
	 *  if case 2 entered from case 1 (end: x will be red_black)
	 *  from case 2 we can go to case (2 or 1) or (3 than 4 end)
	 *
	 *  w != null because x has 2Black color.
	 */
	int colorOf(NodePointer node){
		return ((node == nullptr) ? BinaryNode::BLACK : node->color);
	}

	void removeFexUp(NodePointer x, NodePointer xParent, int isLeftChild){
		NodePointer w;

		if (!x && !xParent)
			return ;
		while (!x || (x != this->_parent && x->color == BinaryNode::BLACK)){
			if (isLeftChild){
				w = xParent->rightChild;
				if (colorOf(w) == BinaryNode::RED){ //case 1
					w->color = BinaryNode::BLACK;
					xParent->color = BinaryNode::RED;
					singleRotationRightToLeft(xParent->getRef(this->_parent));
					w = xParent->rightChild;
				}
				if (colorOf(w->leftChild) == BinaryNode::BLACK && colorOf(w->rightChild) == BinaryNode::BLACK){ //case 2
					w->color = BinaryNode::RED;
					x = xParent;
					xParent = x->parent;
				} else {
					if (colorOf(w->rightChild) == BinaryNode::BLACK){ //case 3
						w->leftChild->color = BinaryNode::BLACK;
						w->color = BinaryNode::RED;
						singleRotationLeftToRight(w->getRef(this->_parent));
						w = w->parent;
					}
					//case 4
					w->color = w->parent->color;
					w->parent->color = BinaryNode::BLACK;
					w->rightChild->color = BinaryNode::BLACK;
					singleRotationRightToLeft(w->parent->getRef(this->_parent));
					x = this->_parent;
				}
			}else{
				w = xParent->leftChild;
				if (colorOf(w) == BinaryNode::RED){ //case 1
					w->color = BinaryNode::BLACK;
					xParent->color = BinaryNode::RED;
					singleRotationLeftToRight(xParent);
					w = xParent->rightChild;
				}
				if (colorOf(w->leftChild) == BinaryNode::BLACK && colorOf(w->rightChild) == BinaryNode::BLACK){ //case 2
					w->color = BinaryNode::RED;
					x = xParent;
					xParent = x->parent;
				} else {
					if (colorOf(w->leftChild) == BinaryNode::BLACK){ //case 3
						w->rightChild->color = BinaryNode::BLACK;
						w->color = BinaryNode::RED;
						singleRotationRightToLeft(w->getRef(this->_parent));
						w = w->parent;
					}
					//case 4
					w->color = w->parent->color;
					w->parent->color = BinaryNode::BLACK;
					w->leftChild->color = BinaryNode::BLACK;
					singleRotationLeftToRight(w->parent->getRef(this->_parent));
					x = this->_parent;
				}
			}
			if (x->parent)
				isLeftChild = (x->parent->leftChild == x);
		}
		x->color = BinaryNode::BLACK;
	}

#pragma endregion

}; //End RedBlackTree


} //End NameSpace

#endif //FT_CONTAINERS_TREE_H
