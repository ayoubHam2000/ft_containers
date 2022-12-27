/*******************************************/
/*     created by aben-ham 11/9/22         */
/*******************************************/

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

#include <iostream>
#include "./type_traits.hpp"

namespace ft{


	/**
	 * @name distance_iterator
	 * @brief calculate the distance between two iterators
	 */
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance_iterator(
			InputIterator first,
			typename enable_if<
					std::is_convertible<typename iterator_traits<InputIterator>::iterator_category , std::input_iterator_tag>::value &&
					!std::is_convertible<typename iterator_traits<InputIterator>::iterator_category, std::random_access_iterator_tag>::value,
					InputIterator
			>::type last
	){
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last){
			first++;
			n++;
		}
		return (n);
	}

	/**
	 * @note an overload of distance_iterator above to work on RandomIterator
	 */
	template <class RandomIterator>
	typename iterator_traits<RandomIterator>::difference_type
	distance_iterator(
			RandomIterator first,
			typename enable_if<
					std::is_convertible<typename iterator_traits<RandomIterator>::iterator_category, std::random_access_iterator_tag>::value,
					RandomIterator
			>::type last
	){
		return last - first;
	}


	//=============================



	template <class T>
	std::string to_string(T n)
	{
		return std::to_string(n);
	}

	template <class T>
	void swap(T &a, T &b){
		T tmp = a;
		a = b;
		b = tmp;
	}

#pragma region pair
	/*****************************************************************/
	// pair
	/*****************************************************************/

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {

		}

		pair(T1 const& t1, T2 const& t2) : first(t1), second(t2) {

		}

		template <class U1, class U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {

		}

		pair &operator=(pair const& p) {
			first = p.first;
			second = p.second;
			return (*this);
		}

		void swap(pair& p) _NOEXCEPT
		{
			ft::swap(first, p.first);
			ft::swap(second, p.second);
		}

	};


	template <class _T1, class _T2>
	bool operator==(const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template <class _T1, class _T2>
	bool operator!=(const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (!(x == y));
	}

	template <class _T1, class _T2>
	bool operator< (const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
	}

	template <class _T1, class _T2>
	bool operator> (const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (y < x);
	}

	template <class _T1, class _T2>
	bool operator>=(const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (!(x < y));
	}

	template <class _T1, class _T2>
	bool operator<=(const pair<_T1, _T2> &x, const pair<_T1, _T2> &y)
	{
		return (!(y < x));
	}

	template <class _T1, class _T2>
	void swap(pair<_T1, _T2> &x, pair<_T1, _T2> &y) _NOEXCEPT
	{
		x.swap(y);
	}

	template <class _T1, class _T2>
	pair<_T1, _T2> make_pair(_T1 x, _T2 y)
	{
		return pair<_T1, _T2>(x, y);
	}

#pragma endregion
}

#endif //FT_CONTAINERS_UTILS_HPP
