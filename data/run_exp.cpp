#include <iostream>
#include "chrono"
#include "../src/page_rank.h"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

int main(int argc, char** argv) {

    auto begin = GET_TIME;

    Matrix a(5,5);

    std::cout << a << std::endl;

    auto end = GET_TIME;

    std::cout << "time:" << GET_TIME_DELTA(begin, end) << std::endl;

}