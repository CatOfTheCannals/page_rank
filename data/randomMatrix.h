#ifndef TP1_METODOS_RANDOMMATRIX_H
#define TP1_METODOS_RANDOMMATRIX_H

#include  "../src/Sparse_matrix_vom.hpp"
Sparse_matrix_vom randomMatrix(int n, int numberOfConnections);
Sparse_matrix_vom randomChainMatrix(int n, int numberOfConnections);
Sparse_matrix_vom directedList(int n);
Sparse_matrix_vom completeColumnAndZeros(int n);
Sparse_matrix_vom completeColumnAndOneBack(int n);
Sparse_matrix_vom chainAndCompleteGraph(int n, int chainSize);

#endif //TP1_METODOS_RANDOMMATRIX_H
