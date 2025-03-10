cmake_minimum_required(VERSION 3.15)

project(left_leaning_red_black_tree)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

include_directories(include)

add_library(RedBlackTree SHARED src/tree.cpp)

set(SOURCES
	src/main.cpp
	src/tree.cpp
) 

add_executable(left_leaning_red_black_tree ${SOURCES} ${HEADERS})
target_link_libraries(left_leaning_red_black_tree PUBLIC RedBlackTree)

enable_testing()
add_subdirectory(test)