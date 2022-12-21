/*******************************************/
/*     created by aben-ham 11/6/22         */
/*******************************************/

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "iterator.hpp"
#include "utils.hpp"
#include "algorithm.hpp"

//TODO Length error max_length
namespace ft{

	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		//typedef std::allocator<T>							allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef vector_iter<const_pointer>					const_iterator;
		typedef vector_iter<pointer>						iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


	private:
		pointer			_first;
		pointer			_last;
		pointer			_last_max;
		allocator_type	_alloc;


	public:

#pragma region Constructors
	/*****************************************************************/
	// Constructors ✅
	/*****************************************************************/

		/**
		 * @name default constructor
		 * @brief Constructs an empty container, with no elements.
		 * The container keeps and uses an internal copy of this allocator.
		 * Member type allocator_type is the internal allocator type used by the container,
		 * defined in vector as an alias of its second template parameter (Alloc).
		 * If in template this second argument is not defined,
		 * std::allocator will be used.
		 * */
		explicit vector(const allocator_type &alloc = allocator_type())
		:
				_first(nullptr),
				_last(nullptr),
				_last_max(nullptr),
				_alloc(alloc)
		{}


		/**
		 * @brief Constructs a container with n elements. Each element is a copy of val.
		 * @param n Initial container _size (i.e., the number of elements in the container at construction).
		 * @param val Value to fill the container with. Each of the n elements in the container will be initialized to a copy of this value.
		 * Member type value_type is the type of the elements in the container, defined in vector as an alias of its first template parameter (T).
		 * @param alloc Allocator object.
		 * The container keeps and uses an internal copy of this allocator.
		 * Member type allocator_type is the internal allocator type used by the container,
		 * defined in vector as an alias of its second template parameter (Alloc).
		 * If in template this second argument is not defined,
		 * std::allocator will be used.
		 */

		explicit vector(
				size_type n,
				const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()
						)
		:
				_first(nullptr),
				_last(nullptr),
				_last_max(nullptr),
				_alloc(alloc)
		{
			insert(begin(), n, val);
		}

		/**
		 * @brief Constructs a container with as many elements as the range [first,last),
		 * with each element constructed from its corresponding element in that range, in the same order.
		 * @param first,last iterators to the initial and final positions in a range.
		 * @param alloc Allocator object.
		 * The container keeps and uses an internal copy of this allocator.
		 * Member type allocator_type is the internal allocator type used by the container,
		 * defined in vector as an alias of its second template parameter (Alloc).
		 * If in template this second argument is not defined,
		 * std::allocator will be used.
		 */

		 //std::is_constructible<value_type, typename iterator_traits<InputIterator>::reference>::value
		template <class InputIterator>
		vector (
				InputIterator first,
				typename enable_if<
				        ft::is_valid_input_iterator<value_type, InputIterator>::value,
						InputIterator
						>::type last,
				const allocator_type& alloc = allocator_type()
				)
	   :
			_first(nullptr),
			_last(nullptr),
			_last_max(nullptr),
			_alloc(alloc)
		{
			insert(begin(), first, last);
		}

		/**
		 * copy constructor
		 * @brief Constructs a container with a copy of each of the elements in x, in the same order.
		 * @param x Another vector object of the same type (with the same class template arguments T and Alloc), whose contents are either copied or acquired.
		 */
		vector (const vector& x)
		:
				_first(nullptr),
				_last(nullptr),
				_last_max(nullptr),
				_alloc(x._alloc)
		{
			insert(this->begin(), x.begin(), x.end());
		}

		~vector(){
			if (_first){
				_destroy_all();
				_alloc.deallocate(_first, capacity());
			}
		}

		vector& operator=(const vector &other){
			clear();
			this->insert(begin(), other.begin(), other.end());
			return (*this);
		}

#pragma endregion

#pragma region Modifiers
	/*****************************************************************/
	// Modifiers (insert ✔, assign ✔, push_back ✔, pop_back ✔, erase ✔, swap ✔, clear ✔) ✔
	/*****************************************************************/

		/**
		 * @param position The position where insert.
		 * @param val The element to insert.
		 * @return iterator An iterator that points to the first of the newly inserted
		 * elements.
		 */
		iterator insert (iterator position, const_reference val){
			size_type pos 		= static_cast<size_type>(&(*position) - _first);
			pointer	  old_last 	= _last;

			bool is_new_space = _shift_to_right(pos, 1);
			if (_first + pos >= old_last || is_new_space)
				_alloc.construct(_first + pos, val);
			else
				(*(_first + pos)) = val;
			return (iterator(_first + pos));
		}

		/**
		 * @name insert
		 * @brief Insert an element a "n" amount of time
		 * before the specified position. Can ecrease de capacity
		 * of the container. This action force the container to
		 * realocate all the elements that were after "position"
		 * to their new positions.
		 *
		 * @param position The position where insert.
		 * @param n Amout of element to insert.
		 * @param val The element to insert.
		 */
		void insert (iterator position, size_type n, const_reference val){
			size_type pos 			= static_cast<size_type>(&(*position) - _first);
			pointer	  old_last 		= _last;

			bool is_new_space = _shift_to_right(pos, n);
			pointer elem = _first + pos;
			while (elem < old_last && n && !is_new_space){
				(*elem) = val;
				++elem;
				--n;
			}
			while (n--){
				_alloc.construct(elem, val);
				++elem;
			}
		}



		/**
		 * @brief Insert element in range from ["first" to
		 * "last") at "position". Can increase the capacity of
		 * the container. Throw if the iterator given is not valid.
		 * Reallocate all elements after the dist between first and last.
		 *
		 * @param position the position where insert.
		 * @param first the first element in the range.
		 * @param last the last element in the range.
		*/
		template <class InputIterator>
		void insert (
				iterator position,
				InputIterator first,
				typename enable_if<
						ft::is_valid_forward_iterator<value_type, InputIterator>::value,
						InputIterator
				>::type last)
		{
			//alloc and shift or just shift
 			size_type n = static_cast<size_type>(distance_iterator(first, last));
			size_type pos = static_cast<size_type>(&(*position) - _first);
			pointer	  old_last = _last;

			bool is_new_space = _shift_to_right(pos, n);
			pointer 		elem 	= _first + pos;
			InputIterator	new_ele = first;
			while (elem < old_last && n && !is_new_space){
				(*elem) = (*new_ele);
				++elem;
				++new_ele;
				--n;
			}
			while (n--){
				_alloc.construct(elem, *new_ele);
				++elem;
				++new_ele;
			}
		}

		template <class InputIterator>
		void insert (
				iterator position,
				InputIterator first,
				typename enable_if<
						ft::is_valid_input_iterator<value_type, InputIterator>::value &&
						!ft::is_valid_forward_iterator<value_type, InputIterator>::value,
						InputIterator
				>::type last)
		{
			size_type 		pos = &(*position) - _first;
			InputIterator	tmp = first;
			while (tmp != last){
				insert(iterator(_first + pos), *tmp);
				++tmp;
				++pos;
			}
		}

		/**
		 * @brief Removes from the vector either a single element (position) or a range of elements ([first,last)).
		 * @param position Iterator pointing to a single element to be removed from the vector.
		 * @param first,last Iterators specifying a range within the vector] to be removed: [first,last). i.e.,
		 * 	the range includes all the elements between first and last, including the element pointed by first but not the one
		 * 	pointed by last.
		 * @return An iterator pointing to the new location of the element that followed the last element erased by
		 * 	the function call. This is the container end if the operation erased the last element in the sequence.
		 */
		iterator erase (iterator position){
			size_type pos = static_cast<size_type>(&(*position) - _first);
			_shift_to_left(pos, 1);
			return (iterator(_first + pos));
		}

		iterator erase (iterator first, iterator last){
			size_type pos = static_cast<size_type>(&(*first) - _first);
			size_type n = static_cast<size_type>(distance_iterator(first, last));
			_shift_to_left(pos, n);
			return (iterator(_first + pos));
		}


		/**
		 * @name assign
		 * @brief Assigns new contents to the vector, replacing its current contents,
		 * and modifying its _size accordingly.
		 */
		template <class InputIterator>
		void assign (
				InputIterator first,
				typename enable_if<
						ft::is_valid_input_iterator<value_type, InputIterator>::value,
						InputIterator
				>::type last
		){
			pointer tmp = _first;
			while (tmp != _last && first != last){
				(*tmp) = (*first);
				++tmp;
				++first;
			}
			if (first != last)
				insert(iterator(_last), first, last);
			else
				erase(iterator(tmp), iterator(_last));
		}

		void assign (size_type n, const_reference val){
			pointer tmp = _first;
			while (tmp != _last && n){
				(*tmp) = val;
				++tmp;
				--n;
			}
			if (n)
				insert(iterator(_last), n, val);
			else
				erase(iterator(tmp), iterator(_last));
		}

		/**
		 * @name push_back
		 * @brief Adds a new element at the end of the vector, after its current last element.
		 */
		void push_back (const_reference val){
			insert(iterator(_last), val);
		}

		/**
		 * @name pop_back
		 * @brief Removes the last element in the vector, effectively reducing the container _size by one.
		 */
		void pop_back(){
			erase(iterator(_last - 1));
		}

		/**
		 * @name swap
		 * @brief Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		 * @details
		 * After the call to this member function, the elements in this container are those which were in x before the call, and the elements of x are those which were in this.
		 * All iterators, references and pointers remain valid for the swapped objects.
		 * Notice that a non-member function exists with the same name, swap, overloading that algorithm with an optimization that behaves like this member function.
		 * @param x Another vector container of the same type (i.e., instantiated with the same template parameters, T and Alloc) whose content is swapped with that of this container.
		 */
		void swap (vector& x){
			ft::swap(this->_first, x._first);
			ft::swap(this->_last, x._last);
			ft::swap(this->_last_max, x._last_max);
		}

		/**
		 * @name clear
		 * @brief Removes all elements from the vector (which are destroyed), leaving the container with a _size of 0.
		 * @detail A reallocation is not guaranteed to happen, and the vector capacity is not guaranteed to change due to calling this function. A typical alternative that forces a reallocation is to use swap
		 */
		void clear() _NOEXCEPT{
			_destroy_all();
		}

#pragma endregion

#pragma region capacity
	/*****************************************************************/
	// Capacity (_size, capacity, max_size, resize, empty, reserve, shrink_to_fit) ✔
	/*****************************************************************/

		/**
		 * @name _size
		 * @return Returns the _size of the vector
		 */

		size_type size() const{
			return static_cast<size_type>(_last - _first);
		}

		/**
		 * @name capacity
		 * @return Returns the capacity of the vector
		 * @note https://stackoverflow.com/questions/5232198/how-does-the-capacity-of-stdvector-grow-automatically-what-is-the-rate#:~:text=The%20capacity%20of%20the%20vector,can%20tell%20how%20it's%20growing..&text=It%20is%20implementation%20dependent%2C%20but,cost%20would%20not%20be%20achieved.
		 * The capacity of the vector is completely implementation-dependent, no one can tell how it's growing..
		 */
		size_type capacity() const{
			return static_cast<size_type>(_last_max - _first);
		}

		/**
		 * @name max_size
		 * @return Returns the maximum number of elements that the vector can hold.
		 */
		size_type max_size() const _NOEXCEPT{
			size_type max_size_diff = std::numeric_limits<difference_type>::max();
			size_type max_size_alloc = _alloc.max_size();
			if (max_size_alloc < max_size_diff)
				return (max_size_alloc);
			return (max_size_diff);
		}

		/**
		 * @brief Resizes the container so that it contains n elements.
		 * @details
		 * If n is smaller than the current container _size, the content is reduced to its first n elements,
		 * 	removing those beyond (and destroying them).
		 * If n is greater than the current container _size, the content is expanded by inserting at the end
		 * 	as many elements as needed to reach a _size of n. If val is specified, the new elements are
		 * 	initialized as copies of val, otherwise, they are value-initialized.
		 * If n is also greater than the current container capacity, an automatic reallocation of the allocated
		 * 	storage space takes place.
		 * Notice that this function changes the actual content of the container by inserting or erasing elements from it.
		 * @param n New container _size, expressed in number of elements.
		 * @param val Object whose content is copied to the added elements in case that n is greater than the current
		 * container _size. If not specified, the default constructor is used instead.
		 */
		void resize (size_type n, value_type val = value_type()){
			if (n < size()){
				erase(iterator(_first + n), iterator(_last));
			}else{
				insert(_last, n - size(), val);
			}
		}

		/**
		 * @name empty
		 * @brief empty Returns whether the vector is empty
		 * @return
		 */
		bool empty() const _NOEXCEPT{
			return (_first == _last);
		}

		/**
		 * @name reserve
		 * @brief Requests that the vector capacity be at least enough to contain n elements.
		 * @details If n is greater than the current vector capacity,
		 * the function causes the container to reallocate its storage increasing its capacity to n (or greater).
		 * In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
		 * This function has no effect on the vector _size and cannot alter its elements.
		 * @param n Minimum capacity for the vector.
		 */
		void reserve (size_type n){
			if (n > capacity()){
				size_type a = __get_new_capacity(n);
				if (a >= max_size() && n < a)
					a = n;
				_add_space(0, 0, n);
			}
		}

		/**
		 * @name shrink_to_fit
		 * @brief Requests the container to reduce its capacity to fit its _size.
		 */
		void shrink_to_fit() _NOEXCEPT{
			if (capacity() > size()){
				try{
					_add_space(0, 0, size());
				}catch (std::bad_alloc &e){
					std::cerr << e.what() << std::endl;
				}
			}
		}



#pragma endregion

#pragma region Iterator
	/*****************************************************************/
	// Iterators (begin, end, rbegin, rend, cbegin, cend, crbegin, crend) ✔
	/*****************************************************************/

		iterator begin() _NOEXCEPT{
			return iterator (_first);
		}

		const_iterator begin() const _NOEXCEPT{
			return const_iterator (_first);
		}

		iterator end() _NOEXCEPT{
			return iterator (_last);
		}

		const_iterator end() const _NOEXCEPT{
			return const_iterator (_last);
		}

		reverse_iterator rbegin() _NOEXCEPT{
			return (reverse_iterator(end()));
		}
		const_reverse_iterator rbegin() const _NOEXCEPT{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend() _NOEXCEPT{
			return (reverse_iterator(begin()));
		}
		const_reverse_iterator rend() const _NOEXCEPT{
			return (const_reverse_iterator(begin()));
		}

		const_iterator cbegin() const _NOEXCEPT{
			return (begin());
		}

		const_iterator cend() const _NOEXCEPT{
			return (end());
		}

		const_reverse_iterator crbegin() const _NOEXCEPT{
			return (rbegin());
		}

		const_reverse_iterator crend() const _NOEXCEPT{
			return (rend());
		}
#pragma endregion

#pragma region Element_access
	/*****************************************************************/
	// Element access (operator[] ✔, at ✔, front ✔,back ✔,data ✔) ✔
	/*****************************************************************/

	/**
	 * @name operator[]
	 * @brief Returns a reference to the element at position n in the vector container.
	 * @details A similar member function, vector::at, has the same behavior as this operator function, except that vector::at
	 * is bound-checked and signals if the requested position is out of range by throwing an out_of_range exception.
	 * Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior.
	 * @return The element at the specified position in the vector.
	 */
	reference operator[] (size_type n){
		return *(_first + n);
	}

	const_reference operator[] (size_type n) const{
		return *(_first + n);
	}

	/**
	 * @name at
	 * @brief Returns a reference to the element at position n in the vector.
	 * @details The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its _size). This is in contrast with member operator[], that does not check against bounds.
	 * @return The element at the specified position in the container.
	 */
	reference at (size_type n){
		if (n >= size())
			_throw_out_of_range(n);
		return *(_first + n);
	}

	const_reference at (size_type n) const{
		if (n >= size())
			_throw_out_of_range(n);
		return *(_first + n);
	}

	/**
	 * @name front
	 * @brief Returns a reference to the first element in the vector.
	 * @return A reference to the first element in the vector container.
	 */
	reference front(){
		return (*_first);
	}

	const_reference front() const{
		return (*_first);
	}

	/**
	 * @name back
	 * @brief Returns a reference to the last element in the vector.
	 * @return A reference to the last element in the vector.
	 */
	reference back(){
		return (*(_last - 1));
	}

	const_reference back() const{
		return (*(_last - 1));
	}

	/**
	 * @name data
	 * @brief Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
	 * @return A pointer to the first element in the array used internally by the vector.
	 */
	pointer data() _NOEXCEPT{
		return (_first);
	}

	const pointer data() const _NOEXCEPT{
		return (_first);
	}

#pragma endregion

#pragma region Allocator
	/*****************************************************************/
	// Allocator (get_allocator)
	/*****************************************************************/

	/**
	 * @name get_allocator
	 * @brief Returns a copy of the allocator object associated with the vector.
	 */
	allocator_type get_allocator() const _NOEXCEPT{
		return (allocator_type (_alloc));
	}




	/*****************************************************************/
	// Private Section
	/*****************************************************************/
#pragma endregion

#pragma region private
		private:

		size_type __get_new_capacity(size_type capacity){
			size_type max_size = this->max_size();
			size_type s = this->capacity();
			if (!s)
				s = 1;
			while (s < capacity && s < max_size)
				s *= 2;
			return (s);
		}

		/**
		 * @note @param pos must be in a valid range in the container
		 * @brief add space to the container and shift elements from pos to the right by nb_shift
		 * @param pos
		 * @param nb_shift
		 */
		void _add_space(size_type pos, size_type nb_shift, size_type new_capacity){
			if (new_capacity > max_size()){
				_throw_max_size();
			}
			size_type capacity = this->capacity();
			size_type size = this->size();
			pointer new_arr = _alloc.allocate(new_capacity);

			//copy and shift
			if (_first){
				pointer dist = new_arr;
				pointer src = _first;
				while (pos--){
					_alloc.construct(dist, *src);
					_alloc.destroy(src);
					++dist;
					++src;
				}
				dist += nb_shift;
				while (src != _last){
					_alloc.construct(dist, *src);
					_alloc.destroy(src);
					++dist;
					++src;
				}
				_alloc.deallocate(_first, capacity);
			}

			//set new member's values
			_first = new_arr;
			_last = new_arr + size + nb_shift;
			_last_max = new_arr + new_capacity;
		}

		void _add_space(size_type pos, size_type nb_shift){
			_add_space(pos, nb_shift, __get_new_capacity(capacity() + nb_shift));
		}

		bool _shift_to_right(size_type pos, size_type nb_shift){
			if (__remains_space() < nb_shift){
				_add_space(pos, nb_shift);
				return (true);
			}
			else if (nb_shift){
				size_type size_copy = this->size() - pos;
				if (_first == _last || !size_copy){
					_last += nb_shift;
					return (false);
				}
				pointer src = _last - 1;
				pointer dist = _last + nb_shift - 1;
				_last += nb_shift;
				while (nb_shift--){
					_alloc.construct(dist, *src);
					--size_copy;
					if (!size_copy)
						return (false);
					--dist;
					--src;
				}
				while (size_copy--){
					(*dist) = (*src);
					--dist;
					--src;
				}
			}
			return (false);
		}

		/**
		 * @bief shift array defined as [pos, end) into the left from @param pos by @param nb_shift
		 * @param pos the position where the shift start
		 * @param nb_shift the number by which the array defined as [pos, end) will be shift to the left, this will override the data in the left
		 * @example [1, 2, 3, 4, 5] shift(2, 2) -> [3, 4, 5, 4, 5]
		 */
		void _shift_to_left(size_type pos, size_type nb_shift){
			size_type nb_copy = _last - (_first + pos + nb_shift);
			pointer	dist = _first + pos;
			pointer src = _first + pos + nb_shift;

			while (nb_copy--){
				(*dist) = (*src);
				++dist;
				++src;
			}
			_last -= nb_shift;
			while (nb_shift--){
				_alloc.destroy(dist);
				++dist;
			}
		}

		void _destroy_all(){
			pointer tmp = _first;
			while (tmp != _last){
				_alloc.destroy(tmp);
				tmp++;
			}
			_last = _first;
		}

		size_type __remains_space(){
			return (static_cast<size_type>(_last_max - _last));
		}

		/**
		 * @note
		 * https://cplusplus.com/reference/vector/vector/insert/
		 * Here is the relevant excerpt from the C++ standard (ISO/IEC 14882:2017(E)):
		 * - If an exception is thrown while attempting to allocate memory, there are no effects.
		 * @param n
		 */
		void _throw_out_of_range(size_type n) const{

			throw std::out_of_range(
					std::string("Vector index out of range vector _size is ") + ft::to_string(size()) +
					std::string(" but got ") + ft::to_string(n) + std::string("."));
		}

		void _throw_max_size() const{
			throw std::length_error("allocation exceeded the maximum allowed _size.");
		}

#pragma endregion


	};

#pragma region relational operators and swap
	/*****************************************************************/
	// Non-member function overloads (relational operators, swap)
	/*****************************************************************/

	/**
	 * @name operator==, operator!=, operator<, operator<=, operator>, bool operator>=
	 * @details
	 * The equality comparison (operator==) is performed by first comparing sizes, and if they match,
	 * the elements are compared sequentially using operator==, stopping at the first mismatch
	 * (as if using algorithm equal).
	 *
	 * The less-than comparison (operator<) behaves as if using algorithm
	 * lexicographical_compare, which compares the elements sequentially using operator< in a reciprocal
	 * manner (i.e., checking both a<b and b<a) and stopping at the first occurrence.
	 *
	 * The other operations also use the operators == and < internally to compare the elements,
	 * behaving as if the following equivalent operations were performed
	 */
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		if (lhs.size() == rhs.size()){
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
		return (false);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !(operator==(lhs, rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (!operator<(rhs, lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (operator<(rhs, lhs));
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return (!operator<(lhs, rhs));
	}

	//TODO Why
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
		x.swap(y);
	}

#pragma endregion

}

#endif //FT_CONTAINERS_VECTOR_HPP
