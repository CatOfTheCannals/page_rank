#include <iostream>
#include "chrono"
#include "../src/page_rank.h"
#include "randomMatrix.h"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

int main(int argc, char** argv) {

    auto begin = GET_TIME;

    Matrix a(5,5);

    std::cout << a << std::endl;

    auto end = GET_TIME;

    std::cout << "time:" << GET_TIME_DELTA(begin, end) << std::endl;

    Matrix b =  randomMatrix(5,5);
    std::cout << "randomMatrix:" << std::endl<< b << std::endl;

    Matrix c =  randomMatrix(5,10);
    std::cout << "randomMatrix:" << std::endl<< c << std::endl;

    Matrix d =  randomMatrix(5,15);
    std::cout << "randomMatrix:" << std::endl<< d << std::endl;

    Matrix e =  randomMatrix(5,19);
    std::cout << "randomMatrix:" << std::endl<< e << std::endl;

    Matrix f =  randomMatrix(5,20);
    std::cout << "randomMatrix:" << std::endl<< f << std::endl;

    Matrix g =  randomMatrix(10,90);
    std::cout << "randomMatrix:" << std::endl<< g << std::endl;

    Matrix h =  randomMatrix(10,20);
    std::cout << "randomMatrix:" << std::endl<< h << std::endl;

    Matrix i =  randomMatrix(10,0);
    std::cout << "randomMatrix:" << std::endl<< i << std::endl;

    Matrix j = randomChainMatrix(5,0);
    std::cout << "randomChainMatrix:" << std::endl<< j << std::endl;

    Matrix k = randomChainMatrix(5,15);
    std::cout << "randomChainMatrix:" << std::endl<< k << std::endl;

    Matrix l = randomChainMatrix(5,10);
    std::cout << "randomChainMatrix:" << std::endl<< l << std::endl;

    Matrix m = conectionsPerColumnRandomMatrix(5,4);
    std::cout << "conectionsPerColumnRandomMatrix:" << std::endl<< m << std::endl;

    Matrix n = conectionsPerColumnRandomMatrix(5,3);
    std::cout << "conectionsPerColumnRandomMatrix:" << std::endl<< n << std::endl;

    Matrix o = conectionsPerColumnRandomMatrix(5,2);
    std::cout << "conectionsPerColumnRandomMatrix:" << std::endl<< o << std::endl;



}