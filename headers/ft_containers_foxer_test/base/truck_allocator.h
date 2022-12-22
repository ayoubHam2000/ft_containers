/*******************************************/
/*     created by aben-ham 12/21/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TRUCK_ALLOCATOR_H
#define FT_CONTAINERS_TRUCK_ALLOCATOR_H

#include <cstddef>
#include <map>
#include <set>
#include <memory>
#include <iostream>

enum dealloc_result {
	DEALLOC_BAD_POINTER,
	DEALLOC_BAD_SIZE,
	DEALLOC_SUCCESS
};

class memory_tracker
{
private:
	static std::map<void*, std::size_t> allocations;
	static std::set<void*> 				constructs;

public:
	static std::size_t allocation_count(){
		return allocations.size();
	}

	static bool allocation_empty(){
		return allocations.empty();
	}

	static std::size_t block_size(void* ptr){
		std::map<void*, std::size_t>::iterator it = allocations.find(ptr);

		return it != allocations.end() ? it->second : 0;
	}

	static void add_allocation(void* ptr, std::size_t size){
		allocations.insert(std::make_pair(ptr, size));
	}

	static dealloc_result remove_allocation(void* ptr, std::size_t size){
		std::map<void*, std::size_t>::iterator it = allocations.find(ptr);

		if (it == allocations.end()) {
			return DEALLOC_BAD_POINTER;
		}
		if (it->second != size) {
			return DEALLOC_BAD_SIZE;
		}

		allocations.erase(it);
		return DEALLOC_SUCCESS;
	}

	static std::size_t constructs_count(){
		return constructs.size();
	}

	static bool constructs_empty(){
		return constructs.empty();
	}

	static bool add_constructor_call(void* ptr){
		std::set<void*>::iterator it = constructs.find(ptr);

		if (it != constructs.end()) {
			return false;
		}

		constructs.insert(ptr);
		return true;
	}

	static bool add_destructor_call(void* ptr){
		std::set<void*>::iterator it = constructs.find(ptr);

		if (it == constructs.end()) {
			return false;
		}

		constructs.erase(ptr);
		return true;
	}



};


std::map<void*, std::size_t> memory_tracker::allocations = std::map<void*, std::size_t>();
std::set<void*> memory_tracker::constructs = std::set<void*>();


struct statistic_track{
	size_t	nb_allocation;
	size_t 	nb_deallocate;
	size_t	nb_construct;
	size_t 	nb_bad_construct;//Called construct on null Or Called construct on initialized memory
	size_t 	nb_destruct;
	size_t 	nb_bad_destruct;//Called destroy on null Or Called destroy on uninitialized memory
	size_t 	nb_bad_size;
	size_t 	nb_bad_deallocate;//deallocate on unconstructed memory region or deallocate a null pointer


	statistic_track(){
		reset();
	}

	statistic_track(const statistic_track& other){
		this->nb_allocation = other.nb_allocation;
		this->nb_deallocate = other.nb_deallocate;
		this->nb_construct = other.nb_construct;
		this->nb_bad_construct = other.nb_bad_construct;
		this->nb_destruct = other.nb_destruct;
		this->nb_bad_destruct = other.nb_bad_destruct;
		this->nb_bad_size = other.nb_bad_size;
		this->nb_bad_deallocate = other.nb_bad_deallocate;
	}

	statistic_track& operator=(const statistic_track& other){
		this->nb_allocation = other.nb_allocation;
		this->nb_deallocate = other.nb_deallocate;
		this->nb_construct = other.nb_construct;
		this->nb_bad_construct = other.nb_bad_construct;
		this->nb_destruct = other.nb_destruct;
		this->nb_bad_destruct = other.nb_bad_destruct;
		this->nb_bad_size = other.nb_bad_size;
		this->nb_bad_deallocate = other.nb_bad_deallocate;
		return (*this);
	}

	~statistic_track(){}

	void reset(){
		nb_allocation = 0;
		nb_deallocate = 0;
		nb_construct = 0;
		nb_bad_construct = 0;
		nb_destruct = 0;
		nb_bad_destruct = 0;
		nb_bad_size = 0;
		nb_bad_deallocate = 0;
	}
};

namespace ft_test{
	statistic_track s;

	void reset_counters(){
		s.reset();
	}
}


template <typename T>
class track_allocator
{
private:
	memory_tracker tracker;

public:
	typedef T              value_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;
	
	template <typename U>
	struct rebind {
		typedef track_allocator<U> other;
	};

public:
	track_allocator()
	{
	}

	track_allocator(const track_allocator&)
	{
	}

	template <typename U>
	track_allocator(const track_allocator<U>&)
	{
	}

	~track_allocator()
	{
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
		tracker.add_allocation((void*)block, n);
		ft_test::s.nb_allocation++;
		return block;
	}

	void deallocate(T* p, std::size_t n)
	{
		if (p == NULL) {
			//Called deallocate on null"
			ft_test::s.nb_bad_deallocate++;
		}

		dealloc_result result = tracker.remove_allocation((void*)p, n);

		switch (result) {
			case DEALLOC_BAD_POINTER:
				//Called deallocate on non-allocated address
				ft_test::s.nb_bad_deallocate++;
				break;
			case DEALLOC_BAD_SIZE:
				//"Called deallocate with wrong block size: "
				ft_test::s.nb_bad_deallocate++;
				break;
			default:;
		}

		ft_test::s.nb_deallocate++;
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
			ft_test::s.nb_bad_construct++;
		}

		const bool result = tracker.add_constructor_call((void*)p);

		if (!result) {
			//Called construct on initialized memory
			ft_test::s.nb_bad_construct++;
		}

		ft_test::s.nb_construct++;
		std::allocator<T>().construct(p, val);
	}

	void destroy(pointer p)
	{
		if (p == NULL) {
			//Called destroy on null"
			ft_test::s.nb_bad_destruct++;
		}

		const bool result = tracker.add_destructor_call((void*)p);

		if (!result) {
			//Called destroy on uninitialized memory: "
			ft_test::s.nb_bad_destruct++;
		}

		ft_test::s.nb_destruct++;
		std::allocator<T>().destroy(p);
	}


};

#endif //FT_CONTAINERS_TRUCK_ALLOCATOR_H
