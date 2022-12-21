/*******************************************/
/*     created by aben-ham 11/20/22         */
/*******************************************/

#ifndef FT_CONTAINERS_MAP_H
#define FT_CONTAINERS_MAP_H

#include "utils.hpp"
#include "algorithm.hpp"
#include "Tree.hpp"

namespace ft{

template <class Key,
		class Tp,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Tp> > >
class  map{
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

		static_assert((std::is_same<typename allocator_type::value_type, value_type>::value),
                  "map::Allocator::value_type must be same type as map::value_type");


		class value_compare
		{
		private:
			key_compare comp;
		public:
			value_compare(): comp(key_compare())  {}
			value_compare(const value_compare &other): comp(other.comp)  {}
			value_compare& operator=(const value_compare &other){
				comp = other.comp;
			}
			~value_compare(){};

			typedef value_type   	first_argument_type;
			typedef value_type   	second_argument_type;
			typedef bool 			result_type;

			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};



private:

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
			return (comp(x.first, y.first));
			//return (comp(x, y));
		}
	private:
		key_compare comp;
	};

	typedef Tree_comparator<value_type, key_compare> 					tree_compare;
	typedef ft::RedBlackTree<value_type, tree_compare, Allocator>		tree;
public:
	typedef typename tree::iterator						iterator;
	typedef typename tree::const_iterator				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
private:
	tree 			_tree;
	key_compare 	_key_com;
	allocator_type	_alloc;
public:
	/*****************************************************************/
	// Constructors
	/*****************************************************************/


	explicit
	map (
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()
		)
			: _tree(tree_compare(comp), alloc), _key_com(comp), _alloc(alloc)
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
		) : _tree(first, last, tree_compare(comp), alloc), _key_com(comp), _alloc(alloc)
	{}

	map (const map& x)
	: _tree(x._tree), _key_com(x._key_com), _alloc(x._alloc)
	{}

	map& operator=(const map& x){
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
		return (_tree.size());
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
		return (_tree.find(v)->second);
	}

	mapped_type& at(const key_type& k){
		iterator res = _tree.find(ft::make_pair(k, mapped_type()));
		if (res == end())
			throw std::out_of_range("Element not inserted!");
		return (res->second);
	}

	const mapped_type& at(const key_type& k) const{
		const_iterator res = _tree.find(ft::make_pair(k, mapped_type()));
		if (res == end())
			throw std::out_of_range("Element not inserted!");
		return (res->second);
	}


	/*****************************************************************/
	// Modifiers (insert, erase, swap, clear)
	/*****************************************************************/

	/*
	 * when iterators are became invalidate ?
	 * @resource https://stackoverflow.com/questions/6438086/iterator-invalidation-rules-for-c-containers/6438087#6438087
	 * insert shall not affect the validity of iterators and references to the container
	 * erase: only iterators and references to the erased elements are invalidated
	 */

	pair<iterator, bool> insert (const_reference val){
		size_type oldSize = _tree.size();
		_tree.insert(val);
		return (ft::make_pair(_tree.find(val), oldSize != _tree.size()));
	}

	iterator insert (iterator position, const_reference val){
		_tree.insert(position, val);
		return (_tree.find(val));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last){
		_tree.insert(first, last);
	}


	void erase (iterator position){
		_tree.remove(*position);
	}

	size_type erase (const key_type& k){
		size_type oldSize = _tree.size();
		_tree.remove(ft::make_pair(k, mapped_type()));
		return (oldSize != _tree.size());
	}

	void erase (iterator first, iterator last){
		_tree.remove(first, last);
	}

	void swap (map& x){
		_tree.swap(x._tree);
	}

	void clear(){
		_tree.clear();
	}

	/*****************************************************************/
	// Observers (key_comp, value_comp, get_allocator)
	/*****************************************************************/

	key_compare key_comp() const{
		return (key_compare(_key_com));
	}

	value_compare value_comp() const{
		return (value_compare());
	}

	allocator_type get_allocator() const{
		return (allocator_type(_alloc));
	}

	//TODO remove it
	void	print(){
		_tree.printTree();
	}

	/*****************************************************************/
	// Operations (find, count, lower_bound, upper_bound, equal_range)
	/*****************************************************************/

	iterator find (const key_type& k){
		return (_tree.find(ft::make_pair(k, mapped_type())));
	}

	const_iterator find (const key_type& k) const{
		return (_tree.find(ft::make_pair(k, mapped_type())));
	}


	size_type count (const key_type& k) const{
		return (size_type(find(k) != end()));
	}

	iterator lower_bound (const key_type& k){
		return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
	}

	const_iterator lower_bound (const key_type& k) const{
		return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
	}

	iterator upper_bound (const key_type& k){
		return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
	}

	const_iterator upper_bound (const key_type& k) const{
		return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
	}

	pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

	pair<iterator,iterator> equal_range (const key_type& k){
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}


};

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator==
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return __x.size() == __y.size() && ft::equal(__x.begin(), __x.end(), __y.begin());
}

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator<
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator!=
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return !(__x == __y);
}

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator>
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return __y < __x;
}

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator>=
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return !(__x < __y);
}

template <class Key, class Tp, class Compare, class Allocator>
inline bool operator<=
	(
		const map<Key, Tp, Compare, Allocator>& __x,
		const map<Key, Tp, Compare, Allocator>& __y
	)
{
	return !(__y < __x);
}

template <class Key, class Tp, class Compare, class Allocator>
inline void swap
		(
			map<Key, Tp, Compare, Allocator>& __x,
	 		map<Key, Tp, Compare, Allocator>& __y
		) _NOEXCEPT
{
	__x.swap(__y);
}

} //End NameSpace Ft

#endif //FT_CONTAINERS_MAP_H
