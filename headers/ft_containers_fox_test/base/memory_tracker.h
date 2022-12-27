//
// Created by aben-ham on 12/22/22.
//

#ifndef FT_CONTAINERS_MEMORY_TRACKER_H
#define FT_CONTAINERS_MEMORY_TRACKER_H

#include <iostream>
#include <map>
#include <set>
#include <memory>
#include <cstddef>
#include "statistic_tracker.h"

enum dealloc_result {
    DEALLOC_BAD_POINTER,
    DEALLOC_BAD_SIZE,
    DEALLOC_SUCCESS
};

class memory_tracker
{
public:
    static std::map<void*, std::size_t> allocations;
    static std::set<void*> 				constructs;
    static statistic_tracker            s;

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

    static void reset();

    static void print();

};

#endif //FT_CONTAINERS_MEMORY_TRACKER_H
