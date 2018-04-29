//
// Created by carlos giudice on 4/22/18.
//

#ifndef TP1_METODOS_SPARSERANDOMMATRIX_H
#define TP1_METODOS_SPARSERANDOMMATRIX_H

#include  "../src/Sparse_matrix_2.hpp"

Sparse_matrix_2 sparseRandomMatrix(int n, int numberOfConnections);
/*
Sparse_matrix_2 randomChainMatrix(int n, int numberOfConnections);
Sparse_matrix_2 directedList(int n);
Sparse_matrix_2 completeColumnAndZeros(int n);
Sparse_matrix_2 conectionsPerColumnRandomMatrix(int n, int connectionsPerColumn); //todo: volvió porque el main de run_exp.cpp la necesitaba (está comentouteada)
Sparse_matrix_2 completeColumnAndOneBack(int n);
Sparse_matrix_2 chainAndCompleteGraph(int n, int chainSize);
*/

#endif //TP1_METODOS_SPARSERANDOMMATRIX_H
