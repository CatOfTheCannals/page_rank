//
// Created by juan on 14/04/18.
//

#ifndef TP1_METODOS_RANDOMMATRIX_H
#define TP1_METODOS_RANDOMMATRIX_H

#include  "../src/Matrix.hpp"
Matrix randomMatrix(int n, int numberOfConnections);
Matrix randomChainMatrix(int n, int numberOfConnections);
Matrix directedList(int n);
Matrix completeColumnAndZeros(int n);
Matrix conectionsPerColumnRandomMatrix(int n, int connectionsPerColumn); //todo: volvió porque el main de run_exp.cpp la necesitaba (está comentouteada)
Matrix completeColumnAndOneBack(int n);
Matrix chainAndCompleteGraph(int n, int chainSize);





#endif //TP1_METODOS_RANDOMMATRIX_H