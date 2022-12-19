/*******************************************/
/*     created by aben-ham 11/16/22         */
/*******************************************/

#ifndef FT_CONTAINERS_TRACK_ALLOC_HPP
#define FT_CONTAINERS_TRACK_ALLOC_HPP

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
public:
	static std::size_t allocation_count();
	static bool allocation_empty();
	static std::size_t block_size(void* ptr);
	static void add_allocation(void* ptr, std::size_t size);
	static dealloc_result remove_allocation(void* ptr, std::size_t size);
	static std::size_t constructs_count();
	static bool constructs_empty();
	static bool add_constructor_call(void* ptr);
	static bool add_destructor_call(void* ptr);

private:
	static std::map<void*, std::size_t> allocations;
	static std::set<void*> constructs;
};

std::size_t memory_tracker::allocation_count()
{
	return allocations.size();
}

bool memory_tracker::allocation_empty()
{
	return allocations.empty();
}

std::size_t memory_tracker::block_size(void* ptr)
{
	std::map<void*, std::size_t>::iterator it = allocations.find(ptr);

	return it != allocations.end() ? it->second : 0;
}

void memory_tracker::add_allocation(void* ptr, std::size_t size)
{
	allocations.insert(std::make_pair(ptr, size));
}

dealloc_result memory_tracker::remove_allocation(void* ptr, std::size_t size)
{
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

std::size_t memory_tracker::constructs_count()
{
	return constructs.size();
}

bool memory_tracker::constructs_empty()
{
	return constructs.empty();
}

bool memory_tracker::add_constructor_call(void* ptr)
{
	std::set<void*>::iterator it = constructs.find(ptr);

	if (it != constructs.end()) {
		return false;
	}

	constructs.insert(ptr);
	return true;
}

bool memory_tracker::add_destructor_call(void* ptr)
{
	std::set<void*>::iterator it = constructs.find(ptr);

	if (it == constructs.end()) {
		return false;
	}

	constructs.erase(ptr);
	return true;
}

std::map<void*, std::size_t> memory_tracker::allocations = std::map<void*, std::size_t>();
std::set<void*> memory_tracker::constructs = std::set<void*>();


















class leak_checker
{
public:
	static void check_leaks();
	static void check_alive_objects();
	static void check_all();

private:
	static memory_tracker tracker;
};




void leak_checker::check_leaks()
{
	if (tracker.allocation_empty()) {
		std::cout << "========================================\n";
		std::cout << "No leak detected\n";
		std::cout << "========================================" << std::endl;
	} else {
		std::cout << "========================================\n";
		std::cout << tracker.allocation_count() << " Leak(s) detected\n";
		std::cout << "========================================" << std::endl;
	}
}

void leak_checker::check_alive_objects()
{
	if (tracker.constructs_empty()) {
		std::cout << "========================================\n";
		std::cout << "Every objects destroyed\n";
		std::cout << "========================================" << std::endl;
	} else {
		std::cout << "========================================\n";
		std::cout << tracker.constructs_count() << " Alive object(s)\n";
		std::cout << "========================================" << std::endl;
	}
}

void leak_checker::check_all()
{
	check_leaks();
	check_alive_objects();
}

memory_tracker leak_checker::tracker = memory_tracker();


#endif //FT_CONTAINERS_TRACK_ALLOC_HPP














template <typename T>
class track_allocator
{
public:
	// clang-format off
	typedef T              value_type;
	typedef T*             pointer;
	typedef const T*       const_pointer;
	typedef T&             reference;
	typedef const T&       const_reference;
	typedef std::size_t    size_type;
	typedef std::ptrdiff_t difference_type;

	// clang-format on

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
		return block;
	}

	void deallocate(T* p, std::size_t n)
	{
		if (p == NULL) {
			std::cout << "Called deallocate on null" << std::endl;
		}

		dealloc_result result = tracker.remove_allocation((void*)p, n);

		switch (result) {
			case DEALLOC_BAD_POINTER:
				std::cout << "Called deallocate on non-allocated address: " << p << std::endl;
				break;
			case DEALLOC_BAD_SIZE:
				std::cout << "Called deallocate with wrong block size: " << n << " (expected "
						  << tracker.block_size(p) << ")" << std::endl;
				break;
			default:;
		}
		std::allocator<T>().deallocate(p, n);
	}

	size_type max_size() const
	{
		return std::allocator<T>().max_size();
	}

	void construct(pointer p, const_reference val)
	{
		if (p == NULL) {
			std::cout << "Called construct on null" << std::endl;
		}

		const bool result = tracker.add_constructor_call((void*)p);

		if (!result) {
			std::cout << "Called construct on initialized memory: " << p << std::endl;
		}

		std::allocator<T>().construct(p, val);
	}

	void destroy(pointer p)
	{
		if (p == NULL) {
			std::cout << "Called destroy on null" << std::endl;
		}

		const bool result = tracker.add_destructor_call((void*)p);

		if (!result) {
			std::cout << "Called destroy on uninitialized memory: " << p << std::endl;
		}

		std::allocator<T>().destroy(p);
	}

private:
	memory_tracker tracker;
};
