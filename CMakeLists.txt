cmake_minimum_required(VERSION 3.6)
project(tp1_metodos CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-long-long -pedantic -Wno-variadic-macros")

set(SOURCE_FILES
        src/empy_file.cpp
        src/Matrix.cpp
        src/Solvers.cpp
        src/page_rank.cpp
        src/Sparse_matrix.cpp
        src/Sparse_solvers.cpp
        src/Sparse_matrix_2.cpp src/sparse_page_rank.cpp src/sparse_page_rank.h)

add_library(metodos-tp1-base ${SOURCE_FILES})

add_executable(main main.cpp)
target_link_libraries(main metodos-tp1-base)

add_subdirectory(test)

add_subdirectory(data)

#Cosas importantes:
#   1) Google test genera su propio main, dejar main.cpp por afuera de SOURCE_FILES para evitar problemas
#   2) Al compilar "main", agregar el archivo main.cpp para que lo ejecute