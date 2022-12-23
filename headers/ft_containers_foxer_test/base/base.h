/*******************************************/
/*     created by aben-ham 12/21/22         */
/*******************************************/

#ifndef FT_CONTAINERS_BASE_H
#define FT_CONTAINERS_BASE_H

#include "../config.h"
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <random>
#include <type_traits>
#include <cstddef>
#include <string>
#include <limits>
#include "memory_tracker.h"
#include "truck_allocator.h"
#include "utils.h"

time_t get_time(void);

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#endif //FT_CONTAINERS_BASE_H