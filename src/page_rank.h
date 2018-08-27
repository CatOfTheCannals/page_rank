#ifndef TP1_METODOS_PAGE_RANK_H
#define TP1_METODOS_PAGE_RANK_H

#include "../src/Solvers.hpp"

#include "chrono"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

Matrix page_rank(Matrix W, Matrix C, double p);

double normalization_coeff(Matrix column);

Matrix colSumDiag(const Matrix& W);

Matrix onesVec(const int n);

#endif //TP1_METODOS_PAGE_RANK_H
