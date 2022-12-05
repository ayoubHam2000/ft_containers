/*******************************************/
/*     created by aben-ham 11/20/22         */
/*******************************************/

#ifndef FT_CONTAINERS_MAP_H
#define FT_CONTAINERS_MAP_H

#include "utils.hpp"
#include "algorithm.hpp"

template <class

template <class Key,
		class Tp,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Tp> > >
class _LIBCPP_TEMPLATE_VIS map{
public:
		typedef Key                                     	key_type;
		typedef Tp                                      	mapped_type;
		typedef ft::pair<const key_type, mapped_type>       value_type;
		typedef Compare                                 	key_compare;
		typedef Allocator                               	allocator_type;
		typedef value_type&                              	reference;
		typedef const value_type&                        	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef
private:
public:
	/*****************************************************************/
	// Constructors ✅
	/*****************************************************************/
};

#endif //FT_CONTAINERS_MAP_H
