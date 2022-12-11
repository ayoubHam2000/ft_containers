/*******************************************/
/*     created by aben-ham 11/20/22         */
/*******************************************/

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft{

	template <class T, class Container = vector<T> >
	class stack{

	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference       	reference;
		typedef typename container_type::const_reference 	const_reference;
	private:
		container_type container;
	public:

		explicit stack (const container_type& container = container_type()) : container(container){

		}

		stack (const stack &other) : container(other.container){

		}

		stack &operator=(const stack &other){
			container = other.container;
			return (*this);
		}

		~stack(){

		}

		bool empty() const _NOEXCEPT{
			return (container.empty());
		}

		size_type size() const{
			return (container._size());
		}

		reference top(){
			return (*(container.end() - 1));
		}

		const_reference top() const{
			return (*(container.end() - 1));
		}

		void push (const_reference val){
			container.push_back(val);
		}

		void pop(){
			container.pop_back();
		}

		void swap (stack& x) _NOEXCEPT {
			container.swap(x.container);
		}

		template <class _T, class _Container>
		friend
		bool operator== (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend
		bool operator<  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

	};


#pragma region relational operators and swap
	/*****************************************************************/
	// Non-member function overloads (relational operators, swap)
	/*****************************************************************/

	template <class T, class Container>
	bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return (lhs.container == rhs.container);
	}

	template <class T, class Container>
	bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return !(operator==(lhs, rhs));
	}

	template <class T, class Container>
	bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return (lhs.container < rhs.container);
	}

	template <class T, class Container>
	bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return (!operator<(rhs, lhs));
	}

	template <class T, class Container>
	bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return (operator<(rhs, lhs));
	}

	template <class T, class Container>
	bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs){
		return (!operator<(lhs, rhs));
	}

	template <class T, class Container>
	void swap (stack<T, Container>& x, stack<T, Container>& y){
		x.swap(y);
	}

#pragma endregion
}

#endif //FT_CONTAINERS_STACK_HPP
