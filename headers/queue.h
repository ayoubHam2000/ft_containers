/*******************************************/
/*     created by aben-ham 11/23/22         */
/*******************************************/

#ifndef FT_CONTAINERS_QUEUE_H
#define FT_CONTAINERS_QUEUE_H

#include "vector.hpp"

namespace ft{

	template <class T, class Container = vector<T> >
	class queue{

	public:
		typedef Container									container_type;
		//typedef vector<T>									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference       	reference;
		typedef typename container_type::const_reference 	const_reference;
	private:
		container_type container;
	public:

		explicit queue (const container_type& container = container_type()) : container(container){

		}

		queue (const queue &other) : container(other.container){

		}

		queue &operator=(const queue &other){
			container = other.container;
			return (*this);
		}

		~queue(){

		}

		bool empty() const _NOEXCEPT{
			return (container.empty());
		}

		size_type size() const{
			return (container._size());
		}

		reference top(){
			return (*(container.begin()));
		}

		const_reference top() const{
			return (*(container.begin()));
		}

		void enqueue (const_reference val){
			container.push_back(val);
		}

		value_type dequeue(){
			value_type res = *container.begin();
			container.erase(container.begin());
			return (res);
		}

		void swap (queue& x) _NOEXCEPT {
			container.swap(x.container);
		}

		template <class _T, class _Container>
		friend
		bool operator== (const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs);

		template <class _T, class _Container>
		friend
		bool operator<  (const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs);

	};


#pragma region relational operators and swap
	/*****************************************************************/
	// Non-member function overloads (relational operators, swap)
	/*****************************************************************/

	template <class T, class Container>
	bool operator== (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return (lhs.container == rhs.container);
	}

	template <class T, class Container>
	bool operator!= (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return !(operator==(lhs, rhs));
	}

	template <class T, class Container>
	bool operator<  (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return (lhs.container < rhs.container);
	}

	template <class T, class Container>
	bool operator<= (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return (!operator<(rhs, lhs));
	}

	template <class T, class Container>
	bool operator>  (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return (operator<(rhs, lhs));
	}

	template <class T, class Container>
	bool operator>= (const queue<T, Container>& lhs, const queue<T, Container>& rhs){
		return (!operator<(lhs, rhs));
	}

	template <class T, class Container>
	void swap (queue<T, Container>& x, queue<T, Container>& y){
		x.swap(y);
	}

#pragma endregion
}

#endif //FT_CONTAINERS_QUEUE_H
