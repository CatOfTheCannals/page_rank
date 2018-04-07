#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "../src/Solvers.hpp"

// --------- SET UP --------------
class mockGaussInput : public ::testing::Test {
protected:
    virtual void SetUp() {
        g.setIndex(0, 0, 1);
        g.setIndex(0, 1, 2);
        g.setIndex(0, 2, 3);
        g.setIndex(1, 0, 4);
        g.setIndex(1, 1, 5);
        g.setIndex(1, 2, 6);
        g.setIndex(2, 0, 7);
        g.setIndex(2, 1, 8);
        g.setIndex(2, 2, 9);
    }
    Matrix g = Matrix(3,3);
};

TEST_F (mockGaussInput, gaussElim){
    std::cout << std::endl;
    std::cout << gauss_elimination(g) << std::endl;
}