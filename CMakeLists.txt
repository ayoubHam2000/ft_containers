cmake_minimum_required(VERSION 3.23)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

#set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(.)



add_executable(ft_containers
        headers/vector.hpp
        headers/test.hpp
        src/containers/vector.cpp
        src/iterators/iterator.cpp
        headers/iterator.hpp
        main.cpp headers/utils.hpp test.cpp headers/algorithm.hpp headers/track_alloc.hpp headers/stack.hpp headers/map.hpp headers/Tree.hpp main.h headers/queue.hpp headers/type_traits.hpp headers/map_prelude.h headers/set.hpp headers/ft_containers_foxer_test/config.h headers/ft_containers_foxer_test/base/base.h headers/ft_containers_foxer_test/foxer.h headers/ft_containers_foxer_test/base/truck_allocator.h headers/iiiiopio.h headers/ft_containers_foxer_test/base/memory_tracker.cpp headers/ft_containers_foxer_test/base/memory_tracker.h headers/ft_containers_foxer_test/base/statistic_tracker.cpp headers/ft_containers_foxer_test/base/statistic_tracker.h headers/ft_containers_foxer_test/base/utils.cpp headers/ft_containers_foxer_test/base/utils.h headers/ft_containers_foxer_test/base/TestOn.hpp headers/ft_containers_foxer_test/base/common.h headers/ft_containers_foxer_test/base/foxer_global.cpp headers/ft_containers_foxer_test/base/FoxerGlobal.h)
