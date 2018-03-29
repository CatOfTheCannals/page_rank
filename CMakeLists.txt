cmake_minimum_required(VERSION 3.6)
project(tp1_metodos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -Wall -Wno-long-long -pedantic -Wno-variadic-macros")

set(SOURCE_FILES
        Matrix.hpp)

set(TEST_FILES
        tests.cpp)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(main ${SOURCE_FILES} main.cpp)
add_executable(correrTests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(correrTests gtest gtest_main)

#Cosas importantes:
#   1) Google test genera su propio main, dejar main.cpp por afuera de SOURCE_FILES para evitar problemas
#   2) Al compilar "main", agregar el archivo main.cpp para que lo ejecute