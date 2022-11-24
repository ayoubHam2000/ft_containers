/*******************************************/
/*     created by aben-ham 11/13/22         */
/*******************************************/

#ifndef FT_CONTAINERS_ALGORITHM_HPP
#define FT_CONTAINERS_ALGORITHM_HPP

#include <iostream>
#include "utils.hpp"

namespace ft{

	/**
	 * @name equal
	 * @brief Test whether the elements in two ranges are equal
	 * Compares the elements in the range [first1,last1) with those in the range
	 * beginning at first2, and returns true if all of the elements in both ranges
	 * match.
	 */
	template <class InputIterator1, class InputIterator2>
	bool equal(
			InputIterator1 first1, InputIterator1 last1, InputIterator2 first2
	){
		for (; first1 != last1; ++first1, ++first2){
			if (*first1 != *first2)
				return false;
		}
		return true;
	}


	/**
	 * @name lexicographical_compare
	 * @brief Returns true if the range [first1,last1] compares lexicographically
	 * less than the range [first2,last2].
	 * A lexicographical comparison is the kind of comparison generally
	 * used to sort words alphabetically in dictionaries; It involves
	 * comparing sequentially the elements that have the same position in both
	 * ranges against each other until one element is not equivalent to the other.
	 * The result of comparing these first non-matching elements is the result of the lexicographical comparison.
	 *
	 * @param first1
	 * Input iterators to the initial and final positions of the first
	 * sequence. The range used is [first1,last1), which contains all the elements
	 * between first1 and last1, including the element pointed by first1 but not the
	 * element pointed by last1.
	 * @param last1
	 * Input iterators to the initial and final positions of the first
	 * sequence. The range used is [first1,last1), which contains all the elements
	 * between first1 and last1, including the element pointed by first1 but not the
	 * element pointed by last1.
	 * @param first2 Input iterators to the initial and final positions of the
	 * second sequence. The range used is [first2,last2).
	 * @param last2 Input iterators to the initial and final positions of the second
	 * sequence. The range used is [first2,last2).
	 */

	template <class T1, class T2 = T1>
	struct less
	{
		bool operator()(const T1 &x, const T1 &y) const {return x < y;}
		bool operator()(const T1 &x, const T2 &y) const {return x < y;}
		bool operator()(const T2 &x, const T1 &y) const {return x < y;}
		bool operator()(const T2 &x, const T2 &y) const {return x < y;}
	};

	//TODO: test
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2)
	{
		return lexicographical_compare(first1, last1, first2, last2,
				ft::less<
				        typename iterator_traits<InputIterator1>::value_type,
						typename iterator_traits<InputIterator2>::value_type
						>()
				);
	};

	template <class _InputIterator1, class _InputIterator2, class _Compare>
	bool lexicographical_compare(
			_InputIterator1 first1,
			_InputIterator1 last1,
			_InputIterator2 first2,
			_InputIterator2 last2,
			_Compare comp)
	{
		while (first1 != last1) {
			if (first2 == last2 || comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			++first1;
			++first2;
		}
		return (false);
	}
}

#endif //FT_CONTAINERS_ALGORITHM_HPP
