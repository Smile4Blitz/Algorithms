cmake_minimum_required (VERSION 3.31.5)

#Setup doctest
include(FetchContent)
FetchContent_Declare(doctest
  GIT_REPOSITORY 	"https://github.com/onqtam/doctest"
  GIT_TAG 		"v2.4.9"
  GIT_SHALLOW		true
)

FetchContent_MakeAvailable(doctest)

LIST(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/contrib")
set(AdditionalCatchParameters)

project (smoke_test_test)
add_executable(smoke_test_test test.cpp)
# set_property(TARGET smoke_test_test PROPERTY CXX_STANDARD 17)
# set_property(TARGET smoke_test_test PROPERTY CXX_STANDARD_REQUIRED ON)

# hardening of diagnostics in theses tests
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic")

# include_directories(../src)

target_link_libraries(smoke_test_test PRIVATE doctest smoke-test)
# target_link_libraries(smoke_test_test Catch2::Catch2)

include(CTest)
include (${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(smoke_test_test
 	EXTRA_ARGS -o report.xml -s -r junit
)