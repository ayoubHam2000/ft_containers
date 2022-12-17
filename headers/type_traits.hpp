/*******************************************/
/*     created by aben-ham 12/14/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

#include <iostream>

namespace ft{

#pragma region iterator_traits

	/*****************************************************************/
	// iterator_traits
	/*****************************************************************/

	/**
	 * @name iterator_traits
	 * @brief Traits class defining properties of iterators.
	 * @details Standard algorithms determine certain properties of the iterators passed to
	 * them and the range they represent by using the members of the corresponding iterator_traits instantiation.
	 * For every iterator type, a corresponding specialization of iterator_traits
	 * class template shall be defined, with at least the following member types defined:
	 * @param difference_type	Type to express the result of subtracting one iterator from another.
	 * @param value_type	The type of the element the iterator can point to.
	 * @param pointer	The type of a pointer to an element the iterator can point to.
	 * @param reference	The type of a reference to an element the iterator can point to.
	 * @param iterator_category (input_iterator_tag, output_iterator_tag, forward_iterator_tag, bidirectional_iterator_tag, random_access_iterator_tag)
	 * The iterator_traits class template comes with a default definition that obtains these types from the iterator
	 * type itself (see below). It is also specialized for pointers (T*) and pointers to const (const T*).
	 * Note that any custom class will have a valid instantiation of iterator_traits if it publicly inherits the base class std::iterator.
	 */
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class T>
	struct iterator_traits<const T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};


#pragma endregion

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
	 * TODO remove reference and const
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


	template<typename T>
	struct _remove_reference {
		typedef T type;
	};

	template<typename T>
	struct _remove_reference<T&> {
		typedef T type;
	};

	template <class T>
	struct has_members_of_iterators
	{
		typedef char valid_type;
		typedef struct { char array[2]; } not_valid_type;

		template <typename U>
		static valid_type __test(
				typename U::difference_type *,
				typename U::value_type *,
				typename U::pointer *,
				typename U::iterator_category *,
				typename _remove_reference<typename U::reference>::type *
		);

		template <typename U>
		static not_valid_type __test(...);

		static const bool value = sizeof(__test<T>(0, 0, 0, 0, 0)) == sizeof(valid_type);
	};

	template <class T>
	struct has_members_of_iterators<T *> : public ft::true_type
	{};

	template <class T>
	struct has_members_of_iterators<const T *> : public ft::true_type
	{};

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
					!is_integral<_Type>::value && has_members_of_iterators<_Type>::value > {};

	template <class _ValueType, class _Type>
	struct is_valid_forward_iterator :
			public __is_valid_iterator<
					_ValueType,
					_Type,
					std::forward_iterator_tag,
					!is_integral<_Type>::value && has_members_of_iterators<_Type>::value > {};

}

#endif //FT_CONTAINERS_TYPE_TRAITS_HPP
