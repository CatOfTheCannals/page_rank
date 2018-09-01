//
// Created by carlos giudice on 4/22/18.
//

#ifndef TP1_METODOS_SPARSERANDOMMATRIX_H
#define TP1_METODOS_SPARSERANDOMMATRIX_H

#include  "../src/Sparse_matrix_vom.hpp"

Sparse_matrix_vom sparseRandomMatrix(int n, int numberOfConnections);
/*
Sparse_matrix_vom randomChainMatrix(int n, int numberOfConnections);
Sparse_matrix_vom directedList(int n);
Sparse_matrix_vom completeColumnAndZeros(int n);
Sparse_matrix_vom conectionsPerColumnRandomMatrix(int n, int connectionsPerColumn); //todo: volvió porque el main de run_exp.cpp la necesitaba (está comentouteada)
Sparse_matrix_vom completeColumnAndOneBack(int n);
Sparse_matrix_vom chainAndCompleteGraph(int n, int chainSize);
*/

#endif //TP1_METODOS_SPARSERANDOMMATRIX_H
