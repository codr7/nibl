cmake_minimum_required(VERSION 3.5)

project(nibl)

set(CMAKE_CXX_COMPILER clang++)

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -O2 -g)

file(GLOB_RECURSE src src/nibl/*.cpp)

add_executable(exe ${src} src/main.cpp)
set_target_properties(exe PROPERTIES OUTPUT_NAME nibl)
target_include_directories(exe PUBLIC src/)

add_library(lib STATIC ${src})
set_target_properties(lib PROPERTIES OUTPUT_NAME nibl)
target_include_directories(lib PUBLIC src/)

install(FILES build/libnibl.a DESTINATION lib)
install(FILES build/nibl DESTINATION bin)
