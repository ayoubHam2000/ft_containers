/*******************************************/
/*     created by aben-ham 11/13/22         */
/*******************************************/

#ifndef FT_CONTAINERS_ALGORITHM_H
#define FT_CONTAINERS_ALGORITHM_H

#include <iostream>
#include "headers/utils.hpp"

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
			InputIterator1 first1, InputIterator1 last1, InputIterator1 first2
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
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(
			InputIterator1 first1,
			InputIterator1 last1,
			InputIterator2 first2,
			InputIterator2 last2)
	{
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};
}

#endif //FT_CONTAINERS_ALGORITHM_H
