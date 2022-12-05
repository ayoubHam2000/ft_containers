/*******************************************/
/*     created by aben-ham 11/7/22         */
/*******************************************/

#ifndef FT_CONTAINERS_ITERATOR_H
#define FT_CONTAINERS_ITERATOR_H

#include <iostream>

namespace ft{

#pragma region iterator_traits

	/*****************************************************************/
	// iterator_traits
	/*****************************************************************/

	/**
	 * @name iterator_traits
	 * @brief Traits class defining properties of iterators.
	 * @details Standard algorithms determine certain properties of the iterators passed to
	 * them and the range they represent by using the members of the corresponding iterator_traits instantiation.
	 * For every iterator type, a corresponding specialization of iterator_traits
	 * class template shall be defined, with at least the following member types defined:
	 * @param difference_type	Type to express the result of subtracting one iterator from another.
	 * @param value_type	The type of the element the iterator can point to.
	 * @param pointer	The type of a pointer to an element the iterator can point to.
	 * @param reference	The type of a reference to an element the iterator can point to.
	 * @param iterator_category (input_iterator_tag, output_iterator_tag, forward_iterator_tag, bidirectional_iterator_tag, random_access_iterator_tag)
	 * The iterator_traits class template comes with a default definition that obtains these types from the iterator
	 * type itself (see below). It is also specialized for pointers (T*) and pointers to const (const T*).
	 * Note that any custom class will have a valid instantiation of iterator_traits if it publicly inherits the base class std::iterator.
	 */
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference 			reference;
		typedef typename Iterator::iterator_category 	iterator_category;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t 						difference_type;
		typedef T 								value_type;
		typedef T* 								pointer;
		typedef T& 								reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
#pragma endregion

#pragma region iterator
	/*****************************************************************/
	// iterator template
	/*****************************************************************/

	/**
	 * @name iterator
	 * @brief This is a base class template that can be used to derive iterator classes from it.
	 * It is not an iterator class and does not provide any of the functionality an iterator is expected to have.
	 * @details This base class only provides some member types, which in fact are not required to be present in any iterator type
	 * (iterator types have no specific member requirements), but they might be useful, since they define the members needed
	 * for the default iterator_traits class template to generate the appropriate instantiation automatically
	 * (and such instantiation is required to be valid for all iterator types).
	 *
	 */

	template <
			class Category,
			class T,
			class Distance = ptrdiff_t,
			class Pointer = T*,
			class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
#pragma endregion

#pragma region reverse iterator
	//TODO: documentation
	/*****************************************************************/
	// reverse_iterator
	/*****************************************************************/

	/**
	 * @name reverse_iterator
	 * @brief This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	 * @details A copy of the original iterator (the base iterator) is kept internally and used to reflect
	 * the operations performed on the reverse_iterator: whenever the reverse_iterator is incremented,
	 * its base iterator is decreased, and vice versa. A copy of the base iterator with the current
	 * state can be obtained at any time by calling member base.
	 *
	 * Notice however that when an iterator is reversed, the reversed version does not point to the same element in
	 * the range, but to the one preceding it. This is so, in order to arrange for the past-the-end element of a
	 * range: An iterator pointing to a past-the-end element in a range, when reversed, is pointing to the last element (not past it)
	 * of the range (this would be the first element of the reversed range). And if an iterator to the first element in a range is reversed,
	 * the reversed iterator points to the element before the first element (this would be the past-the-end element of the reversed range).
	 */
	template <class Iterator>
	class reverse_iterator : public iterator<
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference >
	{

	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer         pointer;
		typedef typename iterator_traits<Iterator>::reference       reference;

	private:
		Iterator current;

	public:
		/**
		 * @brief Constructs a reverse iterator that points to no object.
		 */
		reverse_iterator() : current(){

		}

		/**
		 * @brief Constructs a reverse iterator from some original iterator it. The behavior of the constructed object
		 * replicates the original, except that it iterates through its pointed elements in the reverse order.
		 * @param it An iterator,
		 */
		explicit reverse_iterator (iterator_type it) : current(it){

		}

		/**
		 * @brief Constructs a reverse iterator from some other reverse iterator.
		 * The constructed object keeps the same sense of iteration as rev_it.
		 * @param rev_it An iterator of a reverse_iterator type
		 */
		template <class Iter>  reverse_iterator (const reverse_iterator<Iter>& rev_it) : current(rev_it.base()){

		}

		template <class Iter>
		reverse_iterator &operator=(const reverse_iterator<Iter> &other){
			current = other.base();
			return (*this);
		}

		iterator_type base() const{
			return (current);
		}

		//////////////////////////
		// arithmetic operations
		//////////////////////////

		reverse_iterator operator+ (difference_type n) const{
			return reverse_iterator((current - n));
		}

		reverse_iterator& operator++(){
			--current;
			return (*this);
		}

		reverse_iterator  operator++(int){
			reverse_iterator _tmp(*this);
			--current;
			return (_tmp);
		}

		reverse_iterator& operator+= (difference_type n){
			current -= n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const{
			return reverse_iterator((current + n));
		}

		reverse_iterator& operator--(){
			++current;
			return (*this);
		}

		reverse_iterator  operator--(int){
			reverse_iterator _tmp(*this);
			++current;
			return (_tmp);
		}

		reverse_iterator& operator-= (difference_type n){
			current += n;
			return (*this);
		}

		//////////////////////////
		// other
		//////////////////////////

		/**
		 * @brief Returns a pointer to the element pointed to by the iterator (in order to access one of its members).
		 */
		pointer operator->() const{
			return (&(operator*()));
		}

		/**
		 * @brief Accesses the element located n positions away from the element currently pointed to by the iterator.
		 */
		reference operator[] (difference_type n) const{
			return *(*this + n);
		}

		reference operator*() const{
			Iterator tmp(current);
			return (*(--tmp));
		}



	};


	template <class Iterator1, class Iterator2>
	bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs){
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it){
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
			const reverse_iterator<Iterator1>& lhs,
			const reverse_iterator<Iterator2>& rhs){
		return (rhs.base() - lhs.base());
	}



#pragma endregion

#pragma region vector_iterator

	//TODO: documentation
	/*****************************************************************/
	// vector_iter
	/*****************************************************************/

	/**
	 * @name vector_iter
	 * @note There is not a single type of random-access iterator: Each container may define its own specific
	 * iterator type able to iterate through it and access its elements. But all random access
	 * iterators support -at least- the following operations: https://cplusplus.com/reference/iterator/RandomAccessIterator/
	 */

	template <class Iterator>
	class vector_iter : public iterator<
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type ,
			typename iterator_traits<Iterator>::difference_type ,
			typename iterator_traits<Iterator>::pointer ,
			typename iterator_traits<Iterator>::reference
			>
	{
	public:
		typedef typename iterator_traits<Iterator>::iterator_category 	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type 			value_type;
		typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename iterator_traits<Iterator>::pointer 			pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
	private:
		pointer ptr;

	public:
		vector_iter() : ptr(nullptr){
		}

		vector_iter(pointer x) : ptr(x){

		}


		//for const iterator
		template <class Up>
		vector_iter(const vector_iter<Up> &other): ptr(other.base()){

		}

		template <class Up>
		vector_iter &operator=(const vector_iter<Up> &other){
			this->ptr = other.base();
			return (*this);
		}

		~vector_iter(){}

		pointer base() const{
			return (ptr);
		}

		//////////////////////////
		// arithmetic operations
		//////////////////////////

		vector_iter operator+ (difference_type n) const{
			return (ptr + n);
		}

		vector_iter& operator++(){
			++ptr;
			return (*this);
		}

		vector_iter  operator++(int){
			vector_iter _tmp(*this);
			++ptr;
			return (_tmp);
		}

		vector_iter& operator+= (difference_type n){
			ptr += n;
			return (*this);
		}

		vector_iter operator- (difference_type n) const{
			return (ptr - n);
		}

		vector_iter& operator--(){
			--ptr;
			return (*this);
		}

		vector_iter  operator--(int){
			vector_iter _tmp(*this);
			--ptr;
			return (_tmp);
		}

		vector_iter& operator-= (difference_type n){
			ptr -= n;
			return (*this);
		}

		//////////////////////////
		// other
		//////////////////////////

		pointer operator->() const{
			return (&(operator*()));
		}

		reference operator[] (difference_type n) const{
			return *(*this + n);
		}

		reference operator*() const{
			return (*ptr);
		}

	};


	/* For iterator == const_iterator
	 * exp
	 * ft::vector_iter<int *> y;
	 * ft::vector_iter<const int *> r;
	 * */

	template <class Iterator_1, class Iterator_2>
	bool operator== (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() == rhs.base());
	}

	template <class Iterator_1, class Iterator_2>
	bool operator!= (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() != rhs.base());
	}

	template <class Iterator_1, class Iterator_2>
	bool operator< (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() < rhs.base());
	}

	template <class Iterator_1, class Iterator_2>
	bool operator<= (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator_1, class Iterator_2>
	bool operator> (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() > rhs.base());
	}

	template <class Iterator_1, class Iterator_2>
	bool operator>= (const vector_iter<Iterator_1>& lhs, const vector_iter<Iterator_2>& rhs){
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	typename vector_iter<Iterator1>::difference_type operator-(
			const vector_iter<Iterator1>& lhs,
			const vector_iter<Iterator2>& rhs){
		return (lhs.base() - rhs.base());
	}

	template <class Iterator>
	vector_iter<Iterator> operator+(
			typename vector_iter<Iterator>::difference_type n,
			const vector_iter<Iterator>& rev_it){
		return (rev_it.base() + n);
	}

#pragma endregion

#pragma region vector_iterator

	//TODO: documentation
	/*****************************************************************/
	// vector_iter
	/*****************************************************************/

	template <class Tp, class _NodePtr, class _DiffType>
	class  __tree_iterator
	{
		typedef __tree_node_types<_NodePtr>                     _NodeTypes;
		typedef _NodePtr                                        __node_pointer;
		typedef typename _NodeTypes::__node_base_pointer        __node_base_pointer;
		typedef typename _NodeTypes::__end_node_pointer         __end_node_pointer;
		typedef typename _NodeTypes::__iter_pointer             __iter_pointer;
		typedef pointer_traits<__node_pointer> __pointer_traits;

		__iter_pointer __ptr_;

	public:
		typedef bidirectional_iterator_tag                     iterator_category;
		typedef Tp                                            value_type;
		typedef _DiffType                                      difference_type;
		typedef value_type&                                    reference;
		typedef typename _NodeTypes::__node_value_type_pointer pointer;

#pragma endregion

} //End namespace fd



#endif //FT_CONTAINERS_ITERATOR_H