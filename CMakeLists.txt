cmake_minimum_required(VERSION 3.0)
project(hw_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -O2")
include_directories(src test include)

add_executable(hw_3 src/main.cpp include/huffman_exception.h src/huffman_exception.cpp include/bit_streams.h src/bit_streams.cpp
        include/huffman_tree.h src/huffman_tree.cpp include/huffman_archiver.h src/huffman_archiver.cpp)
add_executable(huffman_test include/huffman_exception.h src/huffman_exception.cpp test/autotest.cpp
        test/autotest.h test/huffman_test.cpp test/huffman_test.h test/test.cpp
        include/bit_streams.h src/bit_streams.cpp include/huffman_tree.h src/huffman_tree.cpp
        include/huffman_archiver.h src/huffman_archiver.cpp)