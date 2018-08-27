#ifndef TP1_METODOS_SPARSE_PAGE_RANK_H
#define TP1_METODOS_SPARSE_PAGE_RANK_H

#ifndef TP1_METODOS_PAGE_RANK_H
#define TP1_METODOS_PAGE_RANK_H

#include "../src/Sparse_solvers.hpp"

#include "chrono"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

Sparse_matrix_vom page_rank(Sparse_matrix_vom W, Sparse_matrix_vom C, double p);

double normalization_coeff(Sparse_matrix_vom column);

Sparse_matrix_vom colSumDiag(const Sparse_matrix_vom& W);

Sparse_matrix_vom onesVec(const int n);

#endif //TP1_METODOS_PAGE_RANK_H


#endif //TP1_METODOS_SPARSE_PAGE_RANK_H
