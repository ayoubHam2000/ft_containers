#include "headers/vector.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

struct Iterator
{
	typedef std::forward_iterator_tag iterator_category;
	typedef     std::ptrdiff_t difference_type;
	typedef      int value_type;
	typedef             int* pointer;
	typedef           int& reference;

	Iterator(pointer ptr) : m_ptr(ptr) {}

	reference operator*() const { return *m_ptr; }
	pointer operator->() { return m_ptr; }
	Iterator& operator++() { m_ptr++; return *this; }
	Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
	friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
	friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

private:
	pointer m_ptr;
};

class Integers
{
public:
	Iterator begin() { return Iterator(&m_data[0]); }
	Iterator end()   { return Iterator(&m_data[200]); }

private:
	int m_data[200];
};


template <class T>
struct has_category{
	typedef T type;
	const static bool value = false;
};

template <>
struct has_category<std::random_access_iterator_tag>{
	const static bool value = true;
};

template <bool>
struct enable_if{};

template <>
struct enable_if<true>{typedef void type;};

int main()
{
	std::enable_if<std::is_convertible<int, int*>::value>::type;
	std::vector<int>::iterator bla;
	std::list<int>::iterator gg;
	std::vector<int>::iterator

	typedef std::vector<int>::iterator::iterator_category iter_Cat;
	iter_Cat  d;
	std::input_iterator_tag ar = d;

	enable_if<has_category<iter_Cat>::value>::type;
	Integers	a;


	struct A{};
	struct B : public A{};

	std::vector<int> new_arr(a.begin(), a.end());
	std::vector<int> dd;
	dd.begin();
	dd.insert(dd.begin(), dd.begin(), dd.end());

	ft::enable_if<std::is_convertible< , float >::value>::type;

}