#ifndef TP1_METODOS_SPARSE_PAGE_RANK_H
#define TP1_METODOS_SPARSE_PAGE_RANK_H

#ifndef TP1_METODOS_PAGE_RANK_H
#define TP1_METODOS_PAGE_RANK_H

#include "../src/Sparse_solvers.hpp"

Sparse_matrix_2 page_rank(Sparse_matrix_2 W, Sparse_matrix_2 C, double p);

double normalization_coeff(Sparse_matrix_2 column);

Sparse_matrix_2 colSumDiag(const Sparse_matrix_2& W);

Sparse_matrix_2 onesVec(const int n);

#endif //TP1_METODOS_PAGE_RANK_H


#endif //TP1_METODOS_SPARSE_PAGE_RANK_H
