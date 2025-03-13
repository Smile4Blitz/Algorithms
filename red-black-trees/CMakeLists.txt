cmake_minimum_required(VERSION 3.15)

project(red_black_interval_tree)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
# Enable the Address Sanitizer
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(RedBlackTree SHARED src/redBlackTree.cpp)

set(SOURCES
	src/main.cpp
	src/redBlackTree.cpp
) 

add_executable(red_black_interval_tree ${SOURCES} ${HEADERS})
target_link_libraries(red_black_interval_tree PUBLIC RedBlackTree)

enable_testing()
add_subdirectory (test)
