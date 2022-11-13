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

}

#endif //FT_CONTAINERS_UTILS_HPP
