#ifndef TP1_METODOS_RANDOMMATRIX_H
#define TP1_METODOS_RANDOMMATRIX_H

#include  "../src/Sparse_matrix_2.hpp"
Sparse_matrix_2 randomMatrix(int n, int numberOfConnections);
Sparse_matrix_2 randomChainMatrix(int n, int numberOfConnections);
Sparse_matrix_2 directedList(int n);
Sparse_matrix_2 completeColumnAndZeros(int n);
Sparse_matrix_2 completeColumnAndOneBack(int n);
Sparse_matrix_2 chainAndCompleteGraph(int n, int chainSize);

#endif //TP1_METODOS_RANDOMMATRIX_H
