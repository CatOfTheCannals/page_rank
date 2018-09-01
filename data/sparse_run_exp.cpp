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

    for(int k = 0; k < repetitions; k++ ) {

        int i = 1;
        int j = 0;
        while(i < n) {

            j = 0;
            while(j < i * (i - 1)) {

                Sparse_matrix_vom W = sparseRandomMatrix(i, j);
                Sparse_matrix_vom C = colSumDiag(W);

                auto begin = GET_TIME;
                page_rank(W, C, p);
                auto end = GET_TIME;

                file << i << "," << j << "," << GET_TIME_DELTA(begin, end) << std::endl;

                if(!(j % 1000) && !k) {
                    std::cout << "i: " << i << " j: " << j << " time it took: " << GET_TIME_DELTA(begin, end) << std::endl;
                }

                j += step;
            }

            i += step;
        }
    }

    file.close();
}


int main(int argc, char** argv) {
    double p = 0.5;
    int step = 3;
    int n = 100;
    int repetitions = 15;
    randomMatrixExp(p, step, n, repetitions);
}