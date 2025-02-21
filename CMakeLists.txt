cmake_minimum_required(VERSION 3.15)

project(smoke_test)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(smoke-test SHARED src/main.cpp)

set(SOURCES
	src/main.cpp
) 

# set(SOURCES
# 	src/main.cpp
# ) 

# set(HEADERS 
# 	src/lib.hpp
# )
			
add_executable(smoke_test ${SOURCES} ${HEADERS})
target_link_libraries(smoke_test PUBLIC smoke-test)

# set_property(TARGET smoke_test PROPERTY CXX_STANDARD 17)
# set_property(TARGET smoke_test PROPERTY CXX_STANDARD_REQUIRED ON)

# Enable the Address Sanitizer
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


enable_testing()
add_subdirectory (test)

