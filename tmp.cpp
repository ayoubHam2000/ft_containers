/*******************************************/
/*     created by aben-ham 11/11/22         */
/*******************************************/

#pragma region RBNode

template <class T>
struct RBNode : public BinaryNode<T> {
private:
	typedef BinaryNode<T>	_base;
public:
	typedef typename _base::value_type		value_type;
	typedef RBNode<T>* 						nodePointer;
public:
	int 			color; //0 red, 1 black

	enum COLOR{
		RED, BLACK
	};

	RBNode() : _base(), color(RED){}

	RBNode(const value_type &data, nodePointer parent = nullptr, nodePointer leftChild = nullptr, nodePointer rightChild = nullptr, int color = RED) :
			_base(data, parent, leftChild, rightChild),
			color(color)
	{}

	RBNode(const RBNode& other) :
			_base(other),
			color(other.color)
	{}

	~RBNode(){}

	RBNode& operator=(const RBNode& other){
		_base::operator=(other);
		color = other.color;
		return (*this);
	}

	/*****************************************************************/
	// Utilities of RBNode
	/*****************************************************************/

	nodePointer getGrandParent(){
		if (this->parent)
			return (this->parent->parent);
		return (nullptr);
	}

	nodePointer getUncle(){
		if (this->parent && this->parent->parent){
			if (this->parent->parent->leftChild == this->parent)
				return (this->parent->parent->rightChild);
			else
				return (this->parent->parent->leftChild);
		}
		return (nullptr);
	}

	virtual int	getColor(){
		return (this->color);
	}
};


#pragma endregion