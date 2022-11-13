/*******************************************/
/*     created by aben-ham 11/7/22         */
/*******************************************/

#ifndef FT_CONTAINERS_ITERATOR_H
#define FT_CONTAINERS_ITERATOR_H

#include <iostream>

namespace ft{

	/**
	 * @name iterator_traits
	 * @tparam Iterator
	 */
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	/**
	 * @name iterator
	 * @tparam Category
	 * @tparam T
	 * @tparam Distance
	 * @tparam Pointer
	 * @tparam Reference
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

	/**
	 * @name reverse_iterator
	 * @tparam _Iter
	 */
	template <class _Iter>
	class reverse_iterator : public iterator<
			typename iterator_traits<_Iter>::iterator_category,
			typename iterator_traits<_Iter>::value_type,
			typename iterator_traits<_Iter>::difference_type,
			typename iterator_traits<_Iter>::pointer,
			typename iterator_traits<_Iter>::reference >
	{

	};

	/**
	 * @name vector_iter
	 * @tparam _Iter
	 */
	template <class _Iter>
	class vector_iter {
	public:
		typedef _Iter 														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category 	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type 		value_type;
		typedef typename iterator_traits<iterator_type>::difference_type 	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer 			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
	private:
		iterator_type _i;
	};


}



#endif //FT_CONTAINERS_ITERATOR_H
