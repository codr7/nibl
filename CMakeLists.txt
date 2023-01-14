cmake_minimum_required(VERSION 3.5)

project(nibl)

set(CMAKE_CXX_COMPILER clang++)

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -O2 -g)

file(GLOB_RECURSE src src/nibl/*.cpp)

add_executable(exe_target ${src} src/main.cpp)
set_target_properties(exe_target PROPERTIES OUTPUT_NAME nibl)
target_include_directories(exe_target PUBLIC src/)

add_library(lib_target STATIC ${src})
set_target_properties(lib_target PROPERTIES OUTPUT_NAME nibl)
target_include_directories(lib_target PUBLIC src/)

install(FILES build/libnibl.a DESTINATION lib)
install(FILES build/nibl DESTINATION bin)
