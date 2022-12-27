cmake_minimum_required(VERSION 3.23)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

#set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra")

include_directories(.)



add_executable(ft_containers
        headers/containers/vector.hpp
        headers/utils/iterator.hpp
        main.cpp headers/utils/utils.hpp headers/utils/algorithm.hpp headers/containers/stack.hpp headers/containers/map.hpp headers/utils/Tree.hpp headers/utils/queue.hpp headers/utils/type_traits.hpp headers/containers/set.hpp headers/ft_containers_fox_test/config.h headers/ft_containers_fox_test/fox.h headers/ft_containers_fox_test/base/truck_allocator.h headers/ft_containers_fox_test/base/memory_tracker.cpp headers/ft_containers_fox_test/base/memory_tracker.h headers/ft_containers_fox_test/base/statistic_tracker.cpp headers/ft_containers_fox_test/base/statistic_tracker.h headers/ft_containers_fox_test/base/TestOn.hpp headers/ft_containers_fox_test/base/common.h headers/ft_containers_fox_test/base/foxer_global.cpp headers/ft_containers_fox_test/base/FoxerGlobal.h headers/ft_containers_fox_test/MainTest.cpp)
