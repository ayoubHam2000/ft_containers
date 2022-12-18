/*******************************************/
/*     created by aben-ham 11/21/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TREE_HPP
#define FT_CONTAINERS_TREE_HPP

#define DUMMY 5

#include <iostream>
#include "queue.hpp"

//TODO remove it
namespace std{
	template <class _T1, class _T2>
	string	to_string(const ft::pair<_T1, _T2> &data){
		return ("(" + to_string(data.first) + ", " + to_string(data.second) + ")");
	}
}

namespace ft{

#pragma region Node
/**
 * @brief A Binary Search node that used in Binary Search Tree and AVL tree
 * @tparam T
 */

template <class T>
struct BinaryNode
{
public:
	typedef T			value_type;
	typedef BinaryNode*	nodePointer;
public:
	value_type		data;
	nodePointer		leftChild;
	nodePointer		rightChild;
	nodePointer		parent;
	int 			height;
	int				color;
public:
	enum COLOR{
		RED, BLACK
	};
public:
	BinaryNode() : data(), leftChild(nullptr), rightChild(nullptr), parent(nullptr), height(0), color(RED){}

	BinaryNode(const value_type &data, nodePointer parent = nullptr, nodePointer leftChild = nullptr, nodePointer rightChild = nullptr) :
			data(data),
			leftChild(leftChild),
			rightChild(rightChild),
			parent(parent),
			height(0),
			color(RED)
	{}

	BinaryNode(const BinaryNode& other) :
			data(other.data),
			leftChild(other.leftChild),
			rightChild(other.rightChild),
			parent(other.parent),
			height(other.height),
			color(other.color)
	{}

	virtual ~BinaryNode(){}

	BinaryNode& operator=(const BinaryNode& other){
		data = other.data;
		leftChild = (other.leftChild);
		rightChild = (other.rightChild);
		parent = (other.parent);
		height = other.height;
		color = other.color;
		return (*this);
	}

public:
	/*****************************************************************/
	// Utilities BinaryNode
	/*****************************************************************/

	//pre-condition parent must not be null
	nodePointer& getRef() const{
		return (this->parent->leftChild == this ? this->parent->leftChild : this->parent->rightChild);
	}

	nodePointer& getRef(nodePointer& root) const{
		return (isNull(this->parent) ? root : getRef());
	}

	//get the closest node that will be greater than '@param node'
	nodePointer greater() const{
		if (this->rightChild != nullptr)
			return (findMin(this->rightChild));
		return (findGreater(this));
	}

	//get the closest node that will be smaller than '@param node'
	nodePointer	smaller() const{
		if (this->leftChild != nullptr)
			return (findMax(this->leftChild));
		return (findSmaller(this));
	}

public:
	/*****************************************************************/
	// RBNode Utilities BinaryNode
	/*****************************************************************/

	nodePointer getGrandParent() const{
		if (this->parent)
			return (this->parent->parent);
		return (nullptr);
	}

	nodePointer getUncle() const{
		if (this->parent && this->parent->parent){
			if (this->parent->parent->leftChild == this->parent)
				return (this->parent->parent->rightChild);
			else
				return (this->parent->parent->leftChild);
		}
		return (nullptr);
	}


public:
	/*****************************************************************/
	// Static Utilities BinaryNode
	/*****************************************************************/

	//min child in the tree starting from the node
	static nodePointer findMin(const nodePointer node){
		if (isNull(node))
			return (nullptr);
		if (isNull(node->leftChild))
			return (node);
		return findMin(node->leftChild);
	}

	//max child in the tree starting from the node
	static nodePointer findMax(const nodePointer node){
		if (isNull(node))
			return (nullptr);
		if (isNull(node->rightChild))
			return (node);
		return (findMax(node->rightChild));
	}

    static int NodeHeight(nodePointer node){
        if (isNull(node))
            return (-1);
        int leftHeight = NodeHeight(node->leftChild);
        int rightHeight = NodeHeight(node->rightChild);
        return (std::max(leftHeight, rightHeight) + 1);
    }

	static BinaryNode createDummy(nodePointer parent = nullptr){
        BinaryNode node = BinaryNode(value_type(), nullptr, nullptr, parent);
        node.color = DUMMY;
		return (node);
	}

	static bool isNull(nodePointer node){
		return (node == nullptr || node->color == DUMMY);
	}

	static bool isNotNull(nodePointer node){
		return (node != nullptr && node->color != DUMMY);
	}

private:

	//get the closest ancestor node that will be greater than '@param node'
	static nodePointer findGreater(const BinaryNode* node){
		if (!node)
			return (nullptr);
		if (node->parent && node->parent->rightChild == node)
			return (findGreater(node->parent));
		return (node->parent);
	}

	//get the closest ancestor node that will be smaller than '@param node'
	static nodePointer findSmaller(const nodePointer node){
		if (!node)
			return (nullptr);
		if (node->parent && node->parent->leftChild == node)
			return (findSmaller(node->parent));
		return (node->parent);
	}



};
#pragma endregion

#pragma region tree_iterator

	//TODO: documentation
	/*****************************************************************/
	// vector_iter
	/*****************************************************************/

	template <class Tp, class NodePtr, class DiffType>
	class  tree_iterator : public iterator<
	        std::bidirectional_iterator_tag,
			typename iterator_traits<NodePtr>::value_type,
			DiffType,
			typename iterator_traits<NodePtr>::pointer,
			typename iterator_traits<NodePtr>::reference
	> {

		typedef iterator<
				std::bidirectional_iterator_tag,
				typename iterator_traits<NodePtr>::value_type,
				DiffType,
				typename iterator_traits<NodePtr>::pointer,
				typename iterator_traits<NodePtr>::reference
		>		_base;

		//typedef NodePtr															node_type;
		//typedef node_type*														node_pointer;
		//typedef node_type**														const_double_pointer;

	public:
		typedef typename _base::iterator_category 				iterator_category;
		typedef typename _base::value_type 						value_type;
		typedef typename _base::difference_type 				difference_type;
		typedef typename _base::reference 						reference;
		typedef typename _base::pointer 						pointer;

		typedef Tp				data_type;
		typedef data_type*										data_pointer;
		typedef data_type&										data_type_reference;

//	typedef const T *;
	private:
		pointer													ptr;

	public:
		tree_iterator() : ptr(nullptr) {}


		tree_iterator(pointer node) : ptr(node) {}


		tree_iterator(const tree_iterator &other):
			ptr(other.ptr)
		{}

		template<class NodePreUp>
		tree_iterator(const tree_iterator<Tp, NodePreUp, DiffType> &other):
			ptr(other.ptr)
		{}


		tree_iterator &operator=(const tree_iterator &other) {
			this->ptr = other.ptr;
			return (*this);
		}


		template<class TpUp, class NodePreUp>
		tree_iterator &operator=(const tree_iterator<TpUp, NodePreUp, DiffType> &other) {
			this->ptr = other.ptr;
			return (*this);
		}

		~tree_iterator() {}

		pointer base() const {
			return (ptr);
		}


		//////////////////////////
		// arithmetic operations
		//////////////////////////

		tree_iterator &operator++() {
			ptr = ptr->greater();
			return (*this);
		}

		tree_iterator operator++(int) {
			tree_iterator _tmp(*this);
			ptr = ptr->greater();
			return (_tmp);
		}

		tree_iterator &operator--() {
			ptr = ptr->smaller();
			return (*this);
		}

		tree_iterator operator--(int) {
			tree_iterator _tmp(*this);
			ptr = ptr->smaller();
			return (_tmp);
		}


		//////////////////////////
		// other
		//////////////////////////

		data_pointer operator->() const {
			return (&(operator*()));
		}

		data_type_reference operator*() const {
			return (ptr->data);
		}

	}; // End tree iterator

	template<class Tp1, class Tp2, class NodePtr1, class NodePtr2, class DiffType>
	bool operator==(const tree_iterator<Tp1, NodePtr1, DiffType> &lhs, const tree_iterator<Tp2, NodePtr2, DiffType> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template<class Tp1, class Tp2, class NodePtr1, class NodePtr2, class DiffType>
	bool operator!=(const tree_iterator<Tp1, NodePtr1, DiffType> &lhs, const tree_iterator<Tp2, NodePtr2, DiffType> &rhs) {
		return (lhs.base() != rhs.base());
	}

#pragma endregion

#pragma region BinaryTree

//Todo: Remove it
template <class T, class key_compare>
struct Tree_comparator{
	Tree_comparator(const key_compare &comp = key_compare()): comp(comp)  {}
	Tree_comparator(const Tree_comparator &other): comp(other.comp)  {}
	Tree_comparator& operator=(const Tree_comparator &other){
		comp = other.comp;
		return (*this);
	}
	~Tree_comparator(){};
	bool operator()(const T& x, const T& y) const{
		return (comp(x, y));
        //return (comp(x.first, y.first));
	}
private:
	key_compare comp;
};

template <
        class T,
		class Compare,
		class Allocator
		>
class BinaryTree{

protected:
	typedef BinaryNode<T>												nodeType;
	typedef nodeType *													nodePointer;
	typedef const BinaryNode<T> *										constNodePointer;

public:
	typedef T                                      						value_type;
	typedef Tree_comparator<T, Compare>                      			value_compare;
	//Compare                      										value_compare;
	typedef Allocator                               					allocator_type;
	typedef typename Allocator::template rebind<nodeType>::other    	node_allocator_type;
	typedef typename allocator_type::size_type							size_type;
	typedef typename allocator_type::difference_type					difference_type;
	typedef typename allocator_type::reference							reference;
	typedef typename allocator_type::const_reference					const_reference;
	typedef tree_iterator<T, nodePointer, difference_type>				iterator;
	typedef tree_iterator<const T, constNodePointer, difference_type>			const_iterator;

protected:
	nodeType 															_dummyNode;
	nodePointer															_parent;
	value_compare														_comp;
	node_allocator_type													_node_alloc;
	size_type 															_size;


public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	BinaryTree(
			const value_compare& comp = value_compare(),
		   	const allocator_type& node_alloc = allocator_type()
			   ) :
            _dummyNode(nodeType::createDummy(nullptr)),
            _parent(&_dummyNode),
            _comp(comp),
            _node_alloc(node_alloc),
            _size(0)
   {
   }

	template <class InputIterator>
	BinaryTree (
		InputIterator first,
		typename enable_if<
				ft::is_valid_input_iterator<value_type, InputIterator>::value,
				InputIterator
		>::type last,
		const value_compare& comp = value_compare(),
		const allocator_type& node_alloc = allocator_type()
	) : _parent(nullptr), _comp(comp), _node_alloc(node_alloc), _size(0)
	{
		insert(first, last);
	}

   BinaryTree(const BinaryTree &other) :
           _dummyNode(nodeType::createDummy(nullptr)),
   			_parent(_clone(other._parent, nullptr)),
		   _comp(other._comp),
		   _node_alloc(other._node_alloc),
		   _size(other._size)
   {}

	BinaryTree &operator=(const BinaryTree &other){
		BinaryTree	tmp(other);
		_destroyTree(_parent);
        this->_dummyNode = tmp._dummyNode;
		this->_parent = tmp._parent;
		this->_node_alloc = tmp._node_alloc;
		this->_comp = tmp._comp;
		this->_size = tmp._size;
		tmp._parent = nullptr;
		return (*this);
	}

	virtual ~BinaryTree(){
		_destroyTree(_parent);
	}


	/*****************************************************************/
	// Utilities BinaryTree
	/*****************************************************************/

	bool isNull(nodePointer node){
		return (nodeType::isNull(node));
	}

	bool isNotNull(nodePointer node){
		return (nodeType::isNotNull(node));
	}

	virtual int height(nodePointer node) const{
		return (nodeType::NodeHeight(node));
	}

	int height(){
		return height(_parent);
	}

	nodePointer findMin(nodePointer node) const{
		return (nodeType::findMin(node));
	}

	nodePointer	findMax(nodePointer node) const{
		return (nodeType::findMax(node));
	}

	nodePointer findMin() const{
		return (nodeType::findMin(_parent));
	}

	nodePointer	findMax() const{
		return (nodeType::findMax(_parent));
	}

	//==========================================
	//iterator
	//==========================================

	iterator getIterator(nodePointer node){
		return (iterator(node));
	}

	const_iterator getIterator(nodePointer node) const{
		return (const_iterator(node));
	}

	iterator begin() _NOEXCEPT{
		return (getIterator(findMin()));
	}

	const_iterator begin() const _NOEXCEPT{
		return (getIterator(findMin()));
	}

	iterator end() _NOEXCEPT{
		iterator res = getIterator(findMax());
        if (res.base() == nullptr)
            return (nullptr);
		return (++res);
	}

	const_iterator end() const _NOEXCEPT{
		const_iterator res = getIterator(findMax());
        if (res.base() == nullptr)
            return (nullptr);
		return (++res);
	}

	iterator	find(const_reference value) {
		return getIterator(findNode(value));
	}

	const_iterator	find(const_reference value) const {
		return getIterator(findNode(value));
	}

	iterator lower_bound (const_reference value){
		return (getIterator(lower_bound(_parent, value)));
	}

	const_iterator lower_bound (const_reference value) const{
		return (getIterator(lower_bound(_parent, value)));
	}

	iterator upper_bound (const_reference value){
		return (getIterator(upper_bound(_parent, value)));
	}

	const_iterator upper_bound (const_reference value) const{
		return (getIterator(upper_bound(_parent, value)));
	}

	//==========================================
	//iterator
	//==========================================

	nodePointer	lower_bound(nodePointer root, const_reference value) const{
		nodePointer prev = nullptr;

		while (isNotNull(root))
		{
			if (_comp(value, root->data))
				prev = root;
			if (_comp(root->data, value)){
				root = root->rightChild;
			} else if (_comp(value, root->data)){
				root = root->leftChild;
			} else {
				return (root);
			}
		}
		return (prev);
	}

	nodePointer	upper_bound(nodePointer root, const_reference value) const{
		nodePointer lower = lower_bound(root, value);
		if (!_comp(value, lower->data) && !_comp(lower->data, value))
			return (lower->greater());
		return (lower);
	}

	size_type size() const{
		return (this->_size);
	}

	size_type max_size() const _NOEXCEPT{
		size_type max_size_diff = std::numeric_limits<difference_type>::max();
		size_type max_size_alloc = _node_alloc.max_size();
		if (max_size_alloc < max_size_diff)
			return (max_size_alloc);
		return (max_size_diff);
	}

	bool empty() const _NOEXCEPT{
		return (_size == 0);
	}

	nodePointer findNode(nodePointer node, const_reference value) const {
		if (isNull(node))
			return (nullptr);
		else if (this->_comp(node->data, value))
			return (findNode(node->rightChild, value));
		else if (this->_comp(value, node->data))
			return (findNode(node->leftChild, value));
		else
			return (node);
	}

	nodePointer findNode(const_reference value) const {
		return (this->findNode(_parent, value));
	}

	void	print_center(std::ostream &os, const std::string &item, size_type buffer_size, int color){
		if (color == nodeType::RED)
			os << "\033[1;31m";
		size_type i = 0;
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
		if (color == nodeType::RED)
			os << "\033[0m";
	}

	void 	print_branches(std::ostream &os, size_type buffer_size){
		size_type i = 0;
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

	void 	printTree(nodeType *node, std::ostream &os, size_t tree_height){
		size_type level_item = tree_height;
		size_type buffer_size = 1;
		size_type item_len = 4;
		while (level_item--){
			buffer_size *= 2;
		}
		buffer_size = item_len * buffer_size;

		size_type level = 1;
		size_type depth = 0;
		size_type type = 1;
		level_item = 1;

		ft::queue<nodePointer> queue;
		ft::queue<bool> is_empty_node;
		queue.enqueue(node);
		while (depth < tree_height){
			if (type == 1){
				nodePointer item = queue.dequeue();
				if (item){
					print_center(os, std::to_string(item->data), buffer_size, item->color);
					queue.enqueue(item->leftChild);
					queue.enqueue(item->rightChild);
					is_empty_node.enqueue(true);
				}else{
					queue.enqueue(nullptr);
					queue.enqueue(nullptr);
					print_center(os, " ", buffer_size, nodeType::BLACK); //"?" to show deleted item
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
						print_branches(os, buffer_size);
					else
						print_center(os, " ", buffer_size, nodeType::BLACK);
				}
				level_item = level;
				type = 1;
				buffer_size /= 2;
				os << "\n";
			}
		}
	}

	void	printTree(std::ostream &os = std::cout){
		int h = height() + 1;
		if (h >= 0)
			printTree(this->_parent, os, h);
	}

	void swap(BinaryTree &x){
		ft::swap(x._parent, _parent);
		ft::swap(x._size, _size);
	}

	void clear(){
		this->_destroyTree(_parent);
	}

	template <class InputIterator>
	void insert(
			InputIterator first,
			typename enable_if<
					ft::is_valid_input_iterator<value_type, InputIterator>::value,
					InputIterator
			>::type last
	)
	{
		InputIterator	tmp = first;
		while (tmp != last){
			insert(*tmp);
			++tmp;
		}
	}

	/**
	 * @details
	 * the rule of the while is to find the right parent
	 * where we can insert the value,
	 * because the value can be larger than the grandparent (if it exist)
	 * pre-requisite root should be != null
	 */
	void insert(iterator position, const_reference value){
		nodePointer root = position.base();
		nodePointer parent;

		while (this->_comp(root->data, value)){
			parent = root->parent;
			if (parent && this->_comp(parent->data, value))
				root = parent;
			else
				break;
		}
		nodePointer &ref = root->getRef(this->_parent);
		insert(ref, value);
	}

	template <class InputIterator>
	void remove(
			InputIterator first,
			typename enable_if<
					ft::is_valid_input_iterator<value_type, InputIterator>::value,
					InputIterator
			>::type last
	)
	{
		InputIterator	tmp = first;
		while (tmp != last){
			remove(*tmp++);
		}
	}

	void insert(const_reference value){
		this->insert(this->_parent, value);
	}

	void remove(const_reference value){
		this->remove(this->_parent, value);
	}

protected:

	virtual void insert(nodePointer &, const_reference ){};
	virtual void remove(nodePointer &, const_reference ){};

protected:
	nodePointer	constructNode(const_reference value, const nodePointer parent = nullptr){
		nodePointer node = this->_node_alloc.allocate(1, nullptr);
		this->_node_alloc.construct(node, nodeType(value, parent));
		this->_size++;
		return (node);
	}

	nodePointer constructNode(const nodePointer other){
		nodePointer node = this->_node_alloc.allocate(1, nullptr);
		this->_node_alloc.construct(node, nodeType(*other));
		this->_size++;
		return (node);
	}

	void deleteNode(nodePointer node){
		this->_node_alloc.destroy(node);
		this->_node_alloc.deallocate(node, 1);
		_size--;
	}

	/**
	 * @details
	 *	  n2             n1
	 *	╭──┴──╮        ╭──┴──╮
	 *  n1    z   *->  x     n2
	 * ╭┴╮                  ╭┴╮
	 * x y                  y z
	 */
	void singleRotationLeftToRight(nodePointer &n2){
		nodePointer n1 = n2->leftChild;
		nodePointer y = n1->rightChild;
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
	void singleRotationRightToLeft(nodePointer &n1){
		nodePointer n2 = n1->rightChild;
		nodePointer y = n2->leftChild;
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
	void doubleRotationLeftRight(nodePointer &n3){
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
	void doubleRotationRightLeft(nodePointer &n1){
		singleRotationLeftToRight(n1->rightChild);
		singleRotationRightToLeft(n1);
	}

	/**
	 * @note
	 * pre-condition: a can't be null, b can take the value null
	 * replace a with b
	 */
	void	Transplant(nodePointer a, nodePointer b){
		if (!a->parent)
			this->_parent = b;
		else if (a->parent->leftChild == a)
			a->parent->leftChild = b;
		else
			a->parent->rightChild = b;
		if (b)
			b->parent = a->parent;
	}

private:
	nodePointer _clone(nodePointer node, nodePointer parent){
		if (isNull(node)){
            if (node){
                _dummyNode.parent = parent;
                return &_dummyNode;
            }
			return (node);
        }
		nodePointer tmp = this->constructNode(node);
		tmp->leftChild = _clone(node->leftChild, tmp);
		tmp->rightChild = _clone(node->rightChild, tmp);
		tmp->parent = parent;
		return (tmp);
	}

	void	_destroyTree(nodePointer &node){
		if (isNotNull(node)){
			_destroyTree(node->leftChild);
			_destroyTree(node->rightChild);
			this->deleteNode(node);
			node = nullptr;
		}
	}


}; //End BinaryClass

#pragma endregion

#pragma region BinarySearchTree

template <
        class T,
		class Compare,
		class Allocator
		>
class BinarySearchTree: public BinaryTree<T, Compare, Allocator >{


private:
	typedef BinaryTree<T, Compare, Allocator >	_base;
protected:
	typedef typename _base::nodeType 						nodeType;
	typedef typename _base::nodePointer 					nodePointer;
public:
	typedef typename _base::value_type                      value_type;
	typedef typename _base::value_compare                   value_compare;
	typedef typename _base::allocator_type                  allocator_type;
	typedef typename _base::reference						reference;
	typedef typename _base::const_reference					const_reference;
public:
	using _base::insert;
	using _base::remove;
public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	explicit BinarySearchTree(
			const value_compare& comp = value_compare(),
			const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{}

	template <class InputIterator>
	BinarySearchTree (
			InputIterator first,
			typename enable_if<
					ft::is_valid_input_iterator<value_type, InputIterator>::value,
					InputIterator
			>::type last,
			const value_compare& comp = value_compare(),
			const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{
		this->insertInto(first, last);
	}

	BinarySearchTree(const BinarySearchTree &other) : _base(other) {}
	BinarySearchTree &operator=(const BinarySearchTree &other){
		_base::operator=(other);
		return (*this);
	}
	virtual ~BinarySearchTree(){}


protected:

	virtual void insert(nodePointer &root, const_reference value){
		insertInto(root, value, nullptr);
	};

	virtual void remove(nodePointer& root, const_reference value){
		if (this->isNull(root))
			return ;
		if (this->_comp(root->data, value)){
            remove(root->rightChild, value);
		} else if (this->_comp(value, root->data)){
            remove(root->leftChild, value);
		} else {
			nodePointer node = root;
			if (!node->leftChild){
				this->Transplant(node, node->rightChild);
			} else if (!node->rightChild){
				this->Transplant(node, node->leftChild);
			} else {
				nodePointer minElem = this->findMin(node->rightChild);
				if (node->rightChild != minElem){
					this->Transplant(minElem, minElem->rightChild);
					minElem->rightChild = node->rightChild;
					minElem->rightChild->parent = minElem;
				}
				this->Transplant(node, minElem);
				minElem->leftChild = node->leftChild;
				minElem->leftChild->parent = minElem;
			}
			this->deleteNode(node);
		}
		balance(root);
	}

	virtual void balance(nodePointer &){}

private:

	void	insertInto(nodePointer &root, const_reference value, nodePointer parent){
		if (this->isNull(root)){
			nodePointer tmp = this->constructNode(value, parent);
            if (root){
                tmp->rightChild = &this->_dummyNode;
                this->_dummyNode.parent = tmp;
            }
            root = tmp;
		}
		else if (this->_comp(root->data, value)){
			insertInto(root->rightChild, value, root);
		}
		else if (this->_comp(value, root->data)){
			insertInto(root->leftChild, value, root);
		}
		balance(root);
	}

};

#pragma endregion

#pragma region AVLTree

template <
        class T,
		class Compare,
		class Allocator
		>
class AVLTree : public BinarySearchTree<T, Compare, Allocator>
{

private:
	typedef BinarySearchTree<T, Compare, Allocator>	_base;
protected:
	typedef typename _base::nodeType 						nodeType;
	typedef typename _base::nodePointer 					nodePointer;
public:
	typedef typename _base::value_type                      value_type;
	typedef typename _base::value_compare                   value_compare;
	typedef typename _base::allocator_type                  allocator_type;
	typedef typename _base::reference						reference;
	typedef typename _base::const_reference					const_reference;
public:
	using _base::insert;

public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	AVLTree(
			const value_compare& comp = value_compare(),
			const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{}

	template <class InputIterator>
	AVLTree (
			InputIterator first,
			typename enable_if<
					ft::is_valid_input_iterator<value_type, InputIterator>::value,
					InputIterator
			>::type last,
			const value_compare& comp = value_compare(),
			const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{
		this->insertInto(first, last);
	}

	AVLTree(const AVLTree &other) : _base(other) {}
	AVLTree &operator=(const AVLTree &other){
		_base::operator=(other);
		return (*this);
	}
	~AVLTree(){}

private:
	/*****************************************************************/
	// Utilities AVLTree
	/*****************************************************************/

	virtual int height(nodePointer node) const{
		return ((this->isNull(node)) ? -1 : node->height);
	}

	virtual void balance(nodePointer &node){
		if (this->isNull(node))
			return ;
		int balance = this->height(node->leftChild) - this->height(node->rightChild);
		if (balance > 1){
			if (this->height(node->leftChild->leftChild) >= this->height(node->leftChild->rightChild))
				this->singleRotationLeftToRight(node);
			else
				this->doubleRotationLeftRight(node);
		}else if (balance < -1){
			if (this->height(node->rightChild->rightChild) >= this->height(node->rightChild->leftChild))
				this->singleRotationRightToLeft(node);
			else
				this->doubleRotationRightLeft(node);
		}
		node->height = std::max(this->height(node->leftChild), this->height(node->rightChild)) + 1;
	}



}; //EndAVLTree

#pragma endregion

#pragma region RedBlackTree
template <
		class T,
		class Compare,
		class Allocator
		>
class RedBlackTree : public BinaryTree<T, Compare, Allocator >{
private:
	typedef BinaryTree<T, Compare, Allocator >		_base;
public:
	typedef typename _base::nodeType 						nodeType;
	typedef typename _base::nodePointer 					nodePointer;
public:
	typedef typename _base::value_type                      value_type;
	typedef typename _base::value_compare                   value_compare;
	typedef typename _base::allocator_type                  allocator_type;
	typedef typename _base::reference						reference;
	typedef typename _base::const_reference					const_reference;
public:
	using _base::insert;
	using _base::remove;

public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/

	RedBlackTree(
			const value_compare& comp = value_compare(),
			const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{}

	template <class InputIterator>
	RedBlackTree (
		InputIterator first,
		typename enable_if<
			ft::is_valid_input_iterator<value_type, InputIterator>::value,
			InputIterator
			>::type last,
		const value_compare& comp = value_compare(),
		const allocator_type& node_alloc = allocator_type()
	) : _base(comp, node_alloc)
	{
		this->insert(first, last);
	}

	RedBlackTree(const RedBlackTree(&other)) : _base(other) {}
	RedBlackTree &operator=(const RedBlackTree(&other)){
		_base::operator=(other);
		return (*this);
	}
	~RedBlackTree(){}


protected:
	/*****************************************************************/
	// Utilities of RedBlackTree
	/*****************************************************************/

	virtual void insert(nodePointer &root, const_reference value){
		_insertInto(root, value);
	};

	virtual void remove(nodePointer &root, const_reference value){
		_removeFrom(root, value);
	};

private:

	void _insertInto(nodePointer &root, const_reference value){
		nodePointer node = root;
		nodePointer parent = nullptr;
		while (node){
			parent = node;
			if (this->_comp(node->data, value))
				node = node->rightChild;
			else if (this->_comp(value, node->data))
				node = node->leftChild;
			else
				return ;
		}
		node = this->constructNode(value, parent);
		if (!parent){
			root = node;
            this->_dummyNode.parent = root;
            root->rightChild = this->_dummyNode;
			root->color = nodeType::BLACK;
		}
		else{
			if (this->_comp(node->data, parent->data))
				parent->leftChild = node;
			else{
                if (parent->rightChild == &this->_dummyNode){
                    node->rightChild = &this->_dummyNode;
                    this->_dummyNode.parent = node;
                }
				parent->rightChild = node;
            }
			__fixUpRedBlackTreeInsert(node);
		}
	}

	void __fixUpRedBlackTreeInsert(nodePointer node){
		while (node != this->_parent && node->parent->color == nodeType::RED){
			nodePointer grandParent = node->getGrandParent();
			if (grandParent){
				nodePointer parent = node->parent;
				nodePointer uncle = node->getUncle();
				if (!uncle || uncle->color == nodeType::BLACK){
					nodePointer &r = grandParent->getRef(this->_parent);
					if (grandParent->leftChild == parent && parent->leftChild == node){
						this->singleRotationLeftToRight(r);
					} else if (grandParent->rightChild == parent && parent->rightChild == node){
						this->singleRotationRightToLeft(r);
					} else if (grandParent->leftChild == parent && parent->rightChild == node){
						this->doubleRotationLeftRight(r);
					} else{
						this->doubleRotationRightLeft(r);
					}
					r->color = nodeType::BLACK;
					r->rightChild->color = nodeType::RED;
					r->leftChild->color = nodeType::RED;
					break ;
				} else {
					if (grandParent != this->_parent)
						grandParent->color = nodeType::RED;
					uncle->color = nodeType::BLACK;
					parent->color = nodeType::BLACK;
					node = grandParent;
				}
			}
		}
	}


	/**
	 * @var node is the node that will be delete that take the value of @param value
	 * @var y is the node that will replace node in case node hase two children, other wise y = node
	 * @var x is the node (or null) that will take the y's color (it will have two colors: itself and y's color)
	 * @var oldColor will save the y's color
	 * @node if y's oldColor is black that will result of deletion of a black node
	 */
	void	_removeFrom(nodePointer &root, const_reference value){
		nodePointer node = root;
		nodePointer x;
		nodePointer y;
		nodePointer xParent;
		int 		isLeftChild;
		int 		oldColor;

		while (this->isNotNull(node)){
			if (this->_comp(value, node->data))
				node = node->leftChild;
			else if (value > node->data)
				node = node->rightChild;
			else
				break ;
		}
		if (this->isNotNull(node)){
			oldColor = node->color;
			isLeftChild = (node->parent && node->parent->leftChild == node);
			if (!node->leftChild){
				x = node->rightChild;
				this->Transplant(node, node->rightChild);
				xParent = node->parent;
			}else if (!node->rightChild){
				x = node->leftChild;
				this->Transplant(node, node->leftChild);
				xParent = node->parent;
			}else{
				y = this->findMin(node->rightChild);
				oldColor = y->color;
				x = y->rightChild;
				xParent = y;
				isLeftChild = 0;
				if (node->rightChild != y){
					this->Transplant(y, x);
					xParent = y->parent;
					isLeftChild = 1;
					y->rightChild = node->rightChild;
					y->rightChild->parent = y;
				}
				this->Transplant(node, y);
				y->leftChild = node->leftChild;
				y->leftChild->parent = y;
				y->color = node->color;
			}
			this->deleteNode(node);
			if (oldColor == nodeType::BLACK)
				__removeFexUp(x, xParent, isLeftChild);
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
	int __colorOf(nodePointer node){
		return ((this->isNull(node)) ? nodeType::BLACK : node->color);
	}

	void __removeFexUp(nodePointer x, nodePointer xParent, int isLeftChild){
		nodePointer w;

		if (this->isNull(x) && !xParent)
			return ;
		while (this->isNull(x) || (x != this->_parent && x->color == nodeType::BLACK)){
			if (isLeftChild){
				w = xParent->rightChild;
				if (__colorOf(w) == nodeType::RED){ //case 1
					w->color = nodeType::BLACK;
					xParent->color = nodeType::RED;
					this->singleRotationRightToLeft(xParent->getRef(this->_parent));
					w = xParent->rightChild;
				}
				if (__colorOf(w->leftChild) == nodeType::BLACK && __colorOf(w->rightChild) == nodeType::BLACK){ //case 2
					w->color = nodeType::RED;
					x = xParent;
					xParent = x->parent;
				} else {
					if (__colorOf(w->rightChild) == nodeType::BLACK){ //case 3
						w->leftChild->color = nodeType::BLACK;
						w->color = nodeType::RED;
						this->singleRotationLeftToRight(w->getRef(this->_parent));
						w = w->parent;
					}
					//case 4
					w->color = w->parent->color;
					w->parent->color = nodeType::BLACK;
					w->rightChild->color = nodeType::BLACK;
					this->singleRotationRightToLeft(w->parent->getRef(this->_parent));
					x = this->_parent;
				}
			}else{
				w = xParent->leftChild;
				if (__colorOf(w) == nodeType::RED){ //case 1
					w->color = nodeType::BLACK;
					xParent->color = nodeType::RED;
					this->singleRotationLeftToRight(xParent);
					w = xParent->rightChild;
				}
				if (__colorOf(w->leftChild) == nodeType::BLACK && __colorOf(w->rightChild) == nodeType::BLACK){ //case 2
					w->color = nodeType::RED;
					x = xParent;
					xParent = x->parent;
				} else {
					if (__colorOf(w->leftChild) == nodeType::BLACK){ //case 3
						w->rightChild->color = nodeType::BLACK;
						w->color = nodeType::RED;
						this->singleRotationRightToLeft(w->getRef(this->_parent));
						w = w->parent;
					}
					//case 4
					w->color = w->parent->color;
					w->parent->color = nodeType::BLACK;
					w->leftChild->color = nodeType::BLACK;
					this->singleRotationLeftToRight(w->parent->getRef(this->_parent));
					x = this->_parent;
				}
			}
			if (x->parent)
				isLeftChild = (x->parent->leftChild == x);
		}
		x->color = nodeType::BLACK;
	}


}; //End RedBlackTree

#pragma endregion

} //End NameSpace

#endif //FT_CONTAINERS_TREE_HPP
