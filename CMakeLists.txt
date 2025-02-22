cmake_minimum_required(VERSION 3.31.5)

project(SmokeAndLabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# Voeg standaard smoke_test toe
include_directories(include)
add_library(smoke-test SHARED src/main.cpp)

set(SOURCES src/main.cpp)
add_executable(smoke_test ${SOURCES})
target_link_libraries(smoke_test PUBLIC smoke-test)

# Enable testing
enable_testing()
add_subdirectory(test)

# Voeg labo-folders toe
add_subdirectory(trees-recap)