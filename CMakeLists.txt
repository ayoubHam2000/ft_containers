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
        main.cpp headers/utils.hpp test.cpp headers/algorithm.hpp headers/track_alloc.hpp headers/stack.hpp headers/map.h headers/Tree.h main.h headers/queue.h headers/type_traits.h)
