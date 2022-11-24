/*******************************************/
/*     created by aben-ham 11/9/22         */
/*******************************************/

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

#include <iostream>

namespace ft{

	/**
	 * @name enable_if
	 * @brief an implementation of std::enable_if : it has a public member typedef type if B is true, otherwise there is no member type
	 * @tparam B
	 */
	template <bool B, class T = void>
	struct enable_if{};

	template <class T>
	struct enable_if<true, T>{
		typedef T type;
	};


	/**
	 * @name false_type
	 * @brief has a member value = false
	 */
	struct false_type {
		static const bool value = false;
	};

	/**
	 * @name false_type
	 * @brief has a member value = true
	 */
	struct true_type {
		static const bool value = true;
	};

	/**
	 * @name is_integral
	 * @brief has a member value = true if @tparam T is integral
	 */
	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<signed char > : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

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

	template <class _ValueType, class _Type, class _To, bool>
	struct __is_valid_iterator{
		static const bool value =
				std::is_convertible<typename iterator_traits<_Type>::iterator_category, _To>::value &&
						std::is_constructible<_ValueType, typename iterator_traits<_Type>::reference>::value;
	};

	template <class _ValueType, class _Type, class _To>
	struct __is_valid_iterator<_ValueType, _Type, _To, false> : public false_type {};

	//
	template <class _ValueType, class _Type>
	struct is_valid_input_iterator :
			public __is_valid_iterator<
			_ValueType,
			_Type,
			std::input_iterator_tag,
			!is_integral<_Type>::value> {};

	template <class _ValueType, class _Type>
	struct is_valid_forward_iterator :
			public __is_valid_iterator<
			_ValueType,
			_Type,
			std::forward_iterator_tag,
			!is_integral<_Type>::value> {};


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

		//TODO Why it is a template
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

	//TODO __is_swappable
	template <class _T1, class _T2>
	typename enable_if
			<
					std::__is_swappable<_T1>::value &&
					std::__is_swappable<_T2>::value,
					void
			>::type
	swap(pair<_T1, _T2> &x, pair<_T1, _T2> &y) _NOEXCEPT
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
