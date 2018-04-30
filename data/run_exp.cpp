#include <iostream>
#include <fstream>
#include <sstream>
#include "chrono"
#include "../src/page_rank.h"
#include "randomMatrix.h"

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
                Matrix W =  randomMatrix(i,j);
                Matrix C = colSumDiag(W);

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

void randomChainMatrixExp(double p, int step, int n, int repetitions) {

    std::ostringstream filename;
    filename << "../../data/results/random_chain_matrix_n_" << n << "_m_" << n * (n-1) << "_p_" << p << ".csv";
    ofstream file;
    file.open(filename.str());

    int i = 1;
    int j = 0;

    while(i < n) {
        while(j < i * i - 2*i) {

            for(int k = 0; k < repetitions; k++ ) {
                Matrix W =  randomChainMatrix(i,j);
                Matrix C = colSumDiag(W);

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

//void conectionsPerColumnRandomMatrixExp(double p, int step, int n, int repetitions) {
//
//    std::ostringstream filename;
//    filename << "../../data/results/connections_per_col_random_matrix_n_" << n << "_m_" << n * (n-1) << "_p_" << p << ".csv";
//    ofstream file;
//    file.open(filename.str());
//
//    int i = 1;
//    int j = 0;
//
//    while(i < n) {
//        while(j < i) {
//
//            for(int k = 0; k < repetitions; k++ ) {
//                Matrix W =  conectionsPerColumnRandomMatrix(i,j);
//                Matrix C = colSumDiag(W);
//
//                auto begin = GET_TIME;
//                page_rank(W, C, p);
//                auto end = GET_TIME;
//
//                file << i << "," << j << "," << GET_TIME_DELTA(begin, end) << std::endl;
//
//                if(!(j % 1000) && !k) {
//                    std::cout << "i: " << i << " Cj: " << j << " time it took: " << GET_TIME_DELTA(begin, end) << std::endl;
//                }
//
//            }
//
//            j += step;
//        }
//
//        i += step;
//    }
//
//    file.close();
//}


int main(int argc, char** argv) {
    double p = 0.5;
    int step = 1;
    int n = 102;
    int repetitions = 5;

    randomMatrixExp(p, step, n, repetitions);

//    for (int i = 1; i < 9; i++) {
//        randomMatrixExp(p * i, step, n, repetitions);
//
//        randomChainMatrixExp(p * i, step, n, repetitions);
//
//        conectionsPerColumnRandomMatrixExp(p * i, step, n, repetitions);
//    }


//
//    Matrix m = conectionsPerColumnRandomMatrix(5,4);
//    std::cout << "conectionsPerColumnRandomMatrix4:" << std::endl<< m << std::endl;
//
//    Matrix n = conectionsPerColumnRandomMatrix(5,3);
//    std::cout << "conectionsPerColumnRandomMatrix3:" << std::endl<< n << std::endl;
//
//    Matrix o = conectionsPerColumnRandomMatrix(5,2);
//    std::cout << "conectionsPerColumnRandomMatrix2:" << std::endl<< o << std::endl;
//
//
//    Matrix p = conectionsPerRowRandomMatrix(5,4);
//    std::cout << "conectionsPerRowRandomMatrix4:" << std::endl<< p << std::endl;
//
//    Matrix q = conectionsPerColumnRandomMatrix(5,3);
//    std::cout << "conectionsPerRowRandomMatrix3:" << std::endl<< q << std::endl;
//
//    Matrix r = conectionsPerColumnRandomMatrix(5,2);
//    std::cout << "conectionsPerRowRandomMatrix2:" << std::endl<< r << std::endl;

    /*
    Matrix s = chainAndCompleteGraph(5,2);
    std::cout << "chainAndCompleteGraph:" << std::endl<< s << std::endl;

    Matrix t = chainAndCompleteGraph(10,5);
    std::cout << "chainAndCompleteGraph:" << std::endl<< t << std::endl;

    Matrix u = chainAndCompleteGraph(10,7);
    std::cout << "chainAndCompleteGraph:" << std::endl<< u << std::endl;

    Matrix v = randomMatrix(10,7);
    std::cout << "randomMatrix:" << std::endl<< v << std::endl;

    Matrix w = randomMatrix(2,2);
    std::cout << "randomMatrix:" << std::endl<< w << std::endl;

    Matrix x = randomChainMatrix(10,5);
    std::cout << "randomChainMatrix:" << std::endl<< x << std::endl;

    Matrix z = randomChainMatrix(10,0);
    std::cout << "randomChainMatrix:" << std::endl<< z << std::endl;

    Matrix a = directedList(10);
    std::cout << "directedList:" << std::endl<< a << std::endl;

    Matrix b = directedList(3);
    std::cout << "directedList:" << std::endl<< b << std::endl;

    Matrix c = completeColumnAndZeros(10);
    std::cout << "completeColumnAndZero:" << std::endl<< c << std::endl;

    Matrix d = completeColumnAndZeros(3);
    std::cout << "completeColumnAndZero:" << std::endl<< d << std::endl;

    Matrix e = completeColumnAndOneBack(10);
    std::cout << "completeColumnAndOneBack:" << std::endl<< e << std::endl;
    */
}