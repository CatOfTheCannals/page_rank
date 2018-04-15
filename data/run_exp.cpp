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


    bool tooLong = false;

    std::ostringstream filename;
    filename << "../../data/results/random_matrix_n" << n << "_m_" << n * (n-1) << "_p_" << p << ".csv";
    ofstream file;
    file.open(filename.str());

    int i = 1;
    int j = 0;

    while(i < n && !tooLong) {
        while(j < i * (i - 1) && !tooLong) {

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

                if (1000000000 < GET_TIME_DELTA(begin, end)) {
                    tooLong = true;
                }
            }

            j += step;
        }

        i += step;
    }

    file.close();
}


int main(int argc, char** argv) {
    double p = 0.1;
    int step = 5;
    int n = 100;
    int repetitions = 5;

    for(int i = 1; i < 9; i++) {
        randomMatrixExp(p * i, step, n, repetitions);

    }


}





