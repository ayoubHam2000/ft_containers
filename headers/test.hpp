/*******************************************/
/*     created by aben-ham 11/6/22         */
/*******************************************/

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "headers/iterator.hpp"

namespace ft{


	//template <class _Tp> struct remove_reference        {typedef _Tp type;};
	//template <class _Tp> struct remove_reference<_Tp&>  {typedef _Tp type;};

	template <class T, class Allocator = std::allocator<T> >
	class vector_base{
	protected:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
	};

	template <class T, class Allocator = std::allocator<T> >
	class vector : private vector_base<T, Allocator>
	{
	private:
		typedef vector_base<T, Allocator>					__base;
	public:
		typedef vector	                                 	 __self;
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename __base::reference					reference;
		typedef typename __base::const_reference			const_reference;
		typedef typename __base::size_type					size_type;
		typedef typename __base::difference_type			difference_type;
		typedef typename __base::pointer					pointer;
		typedef typename __base::const_pointer				const_pointer;
		typedef vector_iter<const_pointer>					const_iterator;
		typedef vector_iter<pointer>						iterator;
		typedef reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef reverse_iterator<iterator>					reverse_iterator;
	private:
		pointer	_start;
		pointer _end;
		pointer _last_max;



		//constructors
		/*
		 default (1)
			explicit vector (const allocator_type& alloc = allocator_type());
			fill (2)
			explicit vector (size_type n, const value_type& val = value_type(),                 const allocator_type& alloc = allocator_type());
			range (3)
			template <class InputIterator>         vector (InputIterator first, InputIterator last,                 const allocator_type& alloc = allocator_type());
			copy (4)
			vector (const vector& x);
		 */

	public:
		//default constructor
		/**
		 * bla bla
		 * @param alloc allocator type
		 * */
		explicit vector(allocator_type &alloc = allocator_type()){}

		/**
		 * dsfsdf
		 * @param a dsf
		 */
		void get(int a){

		}

	};
}

#endif //FT_CONTAINERS_VECTOR_HPP
