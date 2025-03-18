cmake_minimum_required(VERSION 3.10)

project(color_quantization VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
# Enable the Address Sanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fsanitize=address,undefined -fno-omit-frame-pointer")


file(GLOB TARGET_SRC "./src/*.cpp" )
file(COPY images DESTINATION .)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(main ${TARGET_SRC})
