#include <iostream>
#include <fstream>
#include <sstream>
#include "chrono"
#include "../src/sparse_page_rank.h"
#include "sparseRandomMatrix.hpp"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()


void randomMatrixExp(double p, int step, int n, int repetitions) {

    std::ostringstream filename;
    filename << "../../data/results/random_matrix_n_" << n << "_m_" << n * (n-1) << "_p_" << p << ".csv";
    ofstream file;
    file.open(filename.str());

    int i = 1;
    int j = 0;

    while(i < n) {
        while(j < i * (i - 1)) {

            for(int k = 0; k < repetitions; k++ ) {
                Sparse_matrix_2 W = sparseRandomMatrix(i, j);
                Sparse_matrix_2 C = colSumDiag(W);

                auto begin = GET_TIME;
                page_rank(W, C, p);
                auto end = GET_TIME;

                file << i << "," << j << "," << GET_TIME_DELTA(begin, end) << std::endl;

                if(!(j % 1000) && !k) {
                    std::cout << "i: " << i << " j: " << j << " time it took: " << GET_TIME_DELTA(begin, end) << std::endl;
                }

            }

            j += step;
        }

        i += step;
    }

    file.close();
}


int main(int argc, char** argv) {
    double p = 0.5;
    int step = 1;
    int n = 50 vi80;
    int repetitions = 5;

    randomMatrixExp(p, step, n, repetitions);

//    for (int i = 1; i < 9; i++) {
//        randomMatrixExp(p * i, step, n, repetitions);
//    }


//
//    Sparse_matrix_2 m = conectionsPerColumnRandomMatrix(5,4);
//    std::cout << "conectionsPerColumnRandomMatrix4:" << std::endl<< m << std::endl;
//
//    Sparse_matrix_2 n = conectionsPerColumnRandomMatrix(5,3);
//    std::cout << "conectionsPerColumnRandomMatrix3:" << std::endl<< n << std::endl;
//
//    Sparse_matrix_2 o = conectionsPerColumnRandomMatrix(5,2);
//    std::cout << "conectionsPerColumnRandomMatrix2:" << std::endl<< o << std::endl;
//
//
//    Sparse_matrix_2 p = conectionsPerRowRandomMatrix(5,4);
//    std::cout << "conectionsPerRowRandomMatrix4:" << std::endl<< p << std::endl;
//
//    Sparse_matrix_2 q = conectionsPerColumnRandomMatrix(5,3);
//    std::cout << "conectionsPerRowRandomMatrix3:" << std::endl<< q << std::endl;
//
//    Sparse_matrix_2 r = conectionsPerColumnRandomMatrix(5,2);
//    std::cout << "conectionsPerRowRandomMatrix2:" << std::endl<< r << std::endl;

    /*
    Sparse_matrix_2 s = chainAndCompleteGraph(5,2);
    std::cout << "chainAndCompleteGraph:" << std::endl<< s << std::endl;

    Sparse_matrix_2 t = chainAndCompleteGraph(10,5);
    std::cout << "chainAndCompleteGraph:" << std::endl<< t << std::endl;

    Sparse_matrix_2 u = chainAndCompleteGraph(10,7);
    std::cout << "chainAndCompleteGraph:" << std::endl<< u << std::endl;

    Sparse_matrix_2 v = randomMatrix(10,7);
    std::cout << "randomMatrix:" << std::endl<< v << std::endl;

    Sparse_matrix_2 w = randomMatrix(2,2);
    std::cout << "sparseRandomMatrix:" << std::endl<< w << std::endl;

    Sparse_matrix_2 x = randomChainMatrix(10,5);
    std::cout << "randomChainMatrix:" << std::endl<< x << std::endl;

    Sparse_matrix_2 z = randomChainMatrix(10,0);
    std::cout << "randomChainMatrix:" << std::endl<< z << std::endl;

    Sparse_matrix_2 a = directedList(10);
    std::cout << "directedList:" << std::endl<< a << std::endl;

    Sparse_matrix_2 b = directedList(3);
    std::cout << "directedList:" << std::endl<< b << std::endl;

    Sparse_matrix_2 c = completeColumnAndZeros(10);
    std::cout << "completeColumnAndZero:" << std::endl<< c << std::endl;

    Sparse_matrix_2 d = completeColumnAndZeros(3);
    std::cout << "completeColumnAndZero:" << std::endl<< d << std::endl;

    Sparse_matrix_2 e = completeColumnAndOneBack(10);
    std::cout << "completeColumnAndOneBack:" << std::endl<< e << std::endl;
    */
}