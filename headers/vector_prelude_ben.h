/*******************************************/
/*     created by aben-ham 11/19/22         */
/*******************************************/

#ifndef FT_CONTAINERS_VECTOR_PRELUDE_BEN_H
#define FT_CONTAINERS_VECTOR_PRELUDE_BEN_H

#include "vector.hpp"
#include "track_alloc.hpp"
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE std
#endif

#include <sys/time.h>

class timer
{
public:
	timer();

public:
	long get_time();
	void reset();

private:
	struct timeval stamp;
};

#include <cstdlib>

timer::timer()
{
	reset();
}

long timer::get_time()
{
	struct timeval now;
	struct timeval diff;

	gettimeofday(&now, NULL);
	timersub(&now, &stamp, &diff);

	return diff.tv_sec * 1000 + diff.tv_usec / 1000;
}

void timer::reset()
{
	gettimeofday(&stamp, NULL);
}


#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

#define MAXRAM (std::numeric_limits<int>::max())

#define PRINT_TIME(t)                                                                              \
    {                                                                                              \
        std::cout << t.get_time() << "ms" << std::endl;                                            \
    }

#define PRINT_SUM()                                                                                \
    {                                                                                              \
        std::cout << sum << "ms" << std::endl;                                                     \
    }

#define SETUP                                                                                      \
    srand(64);                                                                                     \
    volatile int x = 0;                                                                            \
    (void)x;                                                                                       \
    long sum = 0;                                                                                  \
    (void)sum;

#define BLOCK_OPTIMIZATION(v)                                                                      \
    {                                                                                              \
        if (v[0] == 64) {                                                                          \
            x = x + 64;                                                                            \
        }                                                                                          \
    }

template <typename ForwardIt, typename T>
void iota(ForwardIt first, ForwardIt last, T value = T())
{
	while (first != last) {
		*first++ = value;
		++value;
	}
}


#define MAXSIZE 10000

#endif //FT_CONTAINERS_VECTOR_PRELUDE_BEN_H
