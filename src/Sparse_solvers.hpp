#ifndef TP1_METODOS_SPARSE_SOLVERS_H
#define TP1_METODOS_SPARSE_SOLVERS_H

#include <cassert>
#include <cmath>
#include <chrono>
#include <iostream>
#include <tuple>

#include "Sparse_matrix_vom.hpp"

std::tuple<Sparse_matrix_vom, Sparse_matrix_vom> s_gauss_elimination(const Sparse_matrix_vom& a);

Sparse_matrix_vom backward_sub(const Sparse_matrix_vom& a, const Sparse_matrix_vom& y);

Sparse_matrix_vom forward_sub(const Sparse_matrix_vom& a, const Sparse_matrix_vom& y);

#endif //TP1_METODOS_SPARSE_SOLVERS_H
