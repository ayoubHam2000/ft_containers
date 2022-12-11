/*******************************************/
/*     created by aben-ham 11/20/22         */
/*******************************************/

#ifndef FT_CONTAINERS_MAP_H
#define FT_CONTAINERS_MAP_H

#include "utils.hpp"
#include "algorithm.hpp"
#include "Tree.h"

namespace ft{

template <class Key,
		class Tp,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Tp> > >
class  map{
private:
	typedef ft::RedBlackTree<Key, Compare, Allocator>		tree;
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
		typedef typename allocator_type::size_type          size_type;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename tree::iterator						iterator;
		typedef typename tree::const_iterator				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		//TODO Check What is use for
		class value_compare
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) {}
		public:

			typedef value_type   first_argument_type;
			typedef value_type   second_argument_type;
			typedef bool result_type;

			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};
private:
	tree 			_tree;
	key_compare 	_key_com;
	allocator_type	_alloc;
public:
	/*****************************************************************/
	// Constructors ✅
	/*****************************************************************/


	explicit
	map (
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()
		)
			: _tree(comp, alloc), _key_com(comp), _alloc(alloc)
	{}

	template <class InputIterator>
	map (
		InputIterator first,
		typename enable_if<
				ft::is_valid_input_iterator<value_type, InputIterator>::value,
				InputIterator
		>::type last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()
		) : _tree(comp, alloc), _key_com(comp), _alloc(alloc)
	{
		_insertToTree(first, last);
	}

	map (const map& x)
	: _tree(x._tree), _key_com(x.comp), _alloc(x.alloc)
	{}

	map& operator= (const map& x){
		this->_tree = x._tree;
		this->_alloc = x._alloc;
		this->_key_com = x._key_com;
		return (*this);
	}

	~map(){}

public:

	iterator begin() _NOEXCEPT{
		return iterator (_tree.begin());
	}

	const_iterator begin() const _NOEXCEPT{
		return const_iterator (_tree.begin());
	}

	iterator end() _NOEXCEPT{
		return iterator (_tree.end());
	}

	const_iterator end() const _NOEXCEPT{
		return const_iterator (_tree.end());
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

	/*****************************************************************/
	// Capacity (_size, max_size, empty)
	/*****************************************************************/

	size_type size() const{
		return (_tree._size());
	}

	size_type max_size() const _NOEXCEPT{
		return (_tree.max_size());
	}

	bool empty() const _NOEXCEPT{
		return (_tree.empty());
	}

	/*****************************************************************/
	// Access ([], at)
	/*****************************************************************/

	mapped_type& operator[](const key_type& k){
		value_type	v(ft::make_pair(k, mapped_type()));
		_tree.insert(v);
		return (_tree.get(v).second);
	}

	mapped_type& at(const key_type& k){

	}

	const mapped_type& at(const key_type& k) const{

	}


	/*****************************************************************/
	// Modifiers (insert, erase, swap, clear)
	/*****************************************************************/

	pair<iterator, bool> insert (const_reference val){

	}

	iterator insert (iterator position, const_reference val){

	}

	template <class InputIterator>  void insert (InputIterator first, InputIterator last){

	}

private:

	template <class InputIterator>
	void _insertToTree(
			InputIterator first,
			typename enable_if<
			ft::is_valid_input_iterator<value_type, InputIterator>::value,
			InputIterator
			>::type last)
	{
		InputIterator	tmp = first;
		while (tmp != last){
			_tree.insert(*tmp);
			++tmp;
		}
	}
};

#endif //FT_CONTAINERS_MAP_H

} //End NameSpace Ft