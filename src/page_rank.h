#ifndef TP1_METODOS_PAGE_RANK_H
#define TP1_METODOS_PAGE_RANK_H

#include "../src/Solvers.hpp"

Matrix page_rank(Matrix W, Matrix C, double p);

double normalization_coeff(Matrix column);

Matrix colSumDiag(const Matrix& W);

#endif //TP1_METODOS_PAGE_RANK_H
