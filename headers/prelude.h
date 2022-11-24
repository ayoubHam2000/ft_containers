/*******************************************/
/*     created by aben-ham 11/17/22         */
/*******************************************/

#ifndef FT_CONTAINERS_PRELUDE_H
#define FT_CONTAINERS_PRELUDE_H

#define NAMESPACE ft

#include "track_alloc.hpp"

class leak_checker
{
public:
	static void check_leaks();
	static void check_alive_objects();
	static void check_all();

private:
	static memory_tracker tracker;
};


#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>

#define SEED 64

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

#define PRINT_FILE_LINE()                                                                          \
    {                                                                                              \
        std::cout << " (file: " << __FILE__ << ", line: " << __LINE__ << ")" << std::endl;         \
    }

#define PRINT_LINE(msg, value)                                                                     \
    {                                                                                              \
        std::cout << msg << " " << (value);                                                        \
        PRINT_FILE_LINE();                                                                         \
    }

#define PRINT_MSG(msg)                                                                             \
    {                                                                                              \
        std::cout << msg;                                                                          \
        PRINT_FILE_LINE();                                                                         \
    }

template <typename Iter>
void print_range(Iter first, Iter last)
{
	for (Iter it = first; it != last; ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

#define PRINT_SIZE(c)                                                                              \
    {                                                                                              \
        PRINT_LINE("Size:", c.size());                                                             \
    }

#define CATCH_UNHANDLED_EX()                                                                       \
    catch (...)                                                                                    \
    {                                                                                              \
        std::cout << "unhandled exception";                                                        \
        PRINT_FILE_LINE();                                                                         \
    }

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value = T())
{
	while (first != last) {
		*first++ = value;
		++value;
	}
}

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

#ifdef SINGLE_BINARY
#define MAIN(test_func)
#else
#define MAIN(test_func)                                                                            \
    int main()                                                                                     \
    {                                                                                              \
        srand(SEED);                                                                               \
        test_func();                                                                               \
        leak_checker::check_all();                                                                 \
    }
#endif

struct true_type {
	static const bool value = true;
	typedef true_type type;
};

struct false_type {
	static const bool value = false;
	typedef false_type type;
};

template <typename T, typename U>
struct is_same : public false_type {
};

template <typename T>
struct is_same<T, T> : public true_type {
};

struct big_struct {
	long data[2000];
};


#endif //FT_CONTAINERS_PRELUDE_H
