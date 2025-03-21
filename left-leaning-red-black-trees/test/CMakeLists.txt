cmake_minimum_required(VERSION 3.15)

# Setup doctest
include(FetchContent)
FetchContent_Declare(doctest
  GIT_REPOSITORY "https://github.com/onqtam/doctest"
  GIT_TAG "v2.4.9"
  GIT_SHALLOW true
)
FetchContent_MakeAvailable(doctest)

LIST(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/contrib")
set(AdditionalCatchParameters)

project(red_black_interval_tree_test)
add_executable(red_black_interval_tree_test test.cpp)

target_link_libraries(red_black_interval_tree_test PRIVATE doctest RedBlackTree)

include(CTest)
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(red_black_interval_tree_test
  EXTRA_ARGS -o report.xml -s -r junit
)