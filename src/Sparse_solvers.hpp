#ifndef TP1_METODOS_SPARSE_SOLVERS_H
#define TP1_METODOS_SPARSE_SOLVERS_H

#include <cassert>
#include <cmath>
#include <chrono>
#include <iostream>
#include <tuple>

#include "Sparse_matrix_2.hpp"

std::tuple<Sparse_matrix_2, Sparse_matrix_2> s_gauss_elimination(const Sparse_matrix_2& a);

Sparse_matrix_2 backward_sub(const Sparse_matrix_2& a, const Sparse_matrix_2& y);

Sparse_matrix_2 forward_sub(const Sparse_matrix_2& a, const Sparse_matrix_2& y);

#endif //TP1_METODOS_SPARSE_SOLVERS_H
