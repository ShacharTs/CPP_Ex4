cmake_minimum_required(VERSION 3.30.5)
project(CPP_Ex4)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_Ex4
        container/MyContainer.hpp
        container/MyContainerExceptions.hpp
        main.cpp
        tests/test.cpp
        tests/People.cpp
)
