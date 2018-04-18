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
Matrix completeColumnAndOneBack(int n);
Matrix chainAndCompleteGraph(int n, int chainSize);





#endif //TP1_METODOS_RANDOMMATRIX_H