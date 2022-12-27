/*******************************************/
/*     created by aben-ham 12/21/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TRUCK_ALLOCATOR_H
#define FT_CONTAINERS_TRUCK_ALLOCATOR_H

#include "memory_tracker.h"

template <typename T>
class track_allocator
{
public:
	typedef T              value_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	int state;

	template <typename U>
	struct rebind {
		typedef track_allocator<U> other;
	};

public:
	track_allocator() : state(0)
	{
	}

	track_allocator(const track_allocator& other):state(other.state)
	{
	}

	template <typename U>
	track_allocator(const track_allocator<U>& other):state(other.state)
	{
	}

	~track_allocator()
	{
	}

	track_allocator& operator=(const track_allocator& other){
		this->state = other.state;
		return (*this);
	}

	template <typename U>
	track_allocator& operator=(const track_allocator<U>& other){
		this->state = other.state;
		return(*this);
	}


public:
	bool operator==(const track_allocator&)
	{
		return true;
	}

	bool operator!=(const track_allocator&)
	{
		return false;
	}

public:
	pointer address(reference x) const
	{
		return &x;
	}

	const_pointer address(const_reference x) const
	{
		return &x;
	}

	T* allocate(std::size_t n, const void* hint = 0)
	{
		T* block = std::allocator<T>().allocate(n, hint);
		memory_tracker::add_allocation((void*)block, n);
		memory_tracker::s.nb_allocation++;
		state++;
		return block;
	}

	void deallocate(T* p, std::size_t n)
	{
		if (p == NULL) {
			//Called deallocate on null"
			memory_tracker::s.nb_bad_deallocate++;
		}

		dealloc_result result = memory_tracker::remove_allocation((void*)p, n);

		switch (result) {
			case DEALLOC_BAD_POINTER:
				//Called deallocate on non-allocated address
				memory_tracker::s.nb_bad_deallocate++;
				break;
			case DEALLOC_BAD_SIZE:
				//"Called deallocate with wrong block size: "
				memory_tracker::s.nb_bad_deallocate++;
				break;
			default:;
		}

		memory_tracker::s.nb_deallocate++;
		std::allocator<T>().deallocate(p, n);
	}

	size_type max_size() const
	{
		return std::allocator<T>().max_size();
	}

	void construct(pointer p, const_reference val)
	{
		if (p == NULL) {
			//Called construct on null
			memory_tracker::s.nb_bad_construct++;
		}

		const bool result = memory_tracker::add_constructor_call((void*)p);

		if (!result) {
			//Called construct on initialized memory
			memory_tracker::s.nb_bad_construct++;
		}

		memory_tracker::s.nb_construct++;
		std::allocator<T>().construct(p, val);
	}

	void destroy(pointer p)
	{
		if (p == NULL) {
			//Called destroy on null
			memory_tracker::s.nb_bad_destruct++;
		}

		const bool result = memory_tracker::add_destructor_call((void*)p);

		if (!result) {
			//Called destroy on uninitialized memory: "
			memory_tracker::s.nb_bad_destruct++;
		}

		memory_tracker::s.nb_destruct++;
		std::allocator<T>().destroy(p);
	}


};

#endif //FT_CONTAINERS_TRUCK_ALLOCATOR_H
