cmake_minimum_required(VERSION 3.27)
project(fund_lab1 C)

set(CMAKE_C_STANDARD 17)

include_directories("${PROJECT_SOURCE_DIR}/include")
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*/*.h")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
add_executable(fund_lab1 ${sources})