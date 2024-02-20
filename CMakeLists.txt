cmake_minimum_required(VERSION 3.24)
project(MIVNAI_wet1_new)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MIVNAI_wet1_new
        maina1.cpp
        Olympicsa1.cpp
        Olympicsa1.h
        wet1util.h Node.h AVLTree.h)
