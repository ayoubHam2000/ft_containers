cmake_minimum_required(VERSION 3.23)
project(ft_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(ft_containers
        headers/Vector.hpp
        src/Vector.cpp
        main.cpp)
