#include <iostream>
#include <fstream>
#include <sstream>
#include "chrono"
#include "../src/page_rank.h"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
     std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

int main(int argc, char** argv) {

    auto begin = GET_TIME;

    auto end = GET_TIME;

    std::ostringstream filename;

    filename << "../../data/results/random_" << 5 << ".csv";

    ofstream file ;

    file.open(filename.str());


    file << "time:" << GET_TIME_DELTA(begin, end) << std::endl;

    file.close();
}