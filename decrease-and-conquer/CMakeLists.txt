cmake_minimum_required(VERSION 3.10)

project(decrease_and_conquer)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")

#Setup CSV reader
include(FetchContent)
FetchContent_Declare(csv
  GIT_REPOSITORY 	"https://github.com/vincentlaucsb/csv-parser.git"
  GIT_TAG 		"2.1.3"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(csv)

include_directories(${csv_SOURCE_DIR}/single_include)
include_directories(include)


add_library(knn SHARED src/kNN.cpp)
target_link_libraries(knn csv)

set(SOURCES
	src/main.cpp
) 

add_executable(fake_coin src/fakeCoin.cpp)

add_executable(decrease_and_conquer ${SOURCES})
target_link_libraries(decrease_and_conquer knn)

configure_file(TestSet.csv TestSet.csv COPYONLY)
configure_file(TrainingSet.csv TrainingSet.csv COPYONLY)


enable_testing()
add_subdirectory(test)
