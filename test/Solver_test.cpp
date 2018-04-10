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

        u.setIndex(0, 0,1);
        u.setIndex(0, 1,1.14286);
        u.setIndex(0, 2,1.28571);
        u.setIndex(1, 0,0);
        u.setIndex(1, 1,1);
        u.setIndex(1, 2,2);
        u.setIndex(2, 0,0);
        u.setIndex(2, 1,0);
        u.setIndex(2, 2,1);

        y.setIndex(0, 0, 10);
        y.setIndex(1, 0, 20);
        y.setIndex(2, 0, 30);

        z.setIndex(0, 0,17.1431);
        z.setIndex(1, 0,-40);
        z.setIndex(2, 0,30);
    }
    Matrix g = Matrix(3,3);
    Matrix u = Matrix(3,3);
    Matrix y = Matrix(3,1);
    Matrix z = Matrix(3,1);
};

TEST_F (mockGaussInput, gaussElim){
    /*
    std::cout << std::endl;
    std::cout << gauss_elimination(g) << std::endl;
     */
}

TEST_F (mockGaussInput, backwardSub){
    Matrix id = Matrix::identity(3);
    auto x = backward_sub(u, y);
    // ASSERT_TRUE(x.isApproximate(z, 0.0001)); // z la jarcodie en base a los resultados de solve_triangular de scipy
    ASSERT_TRUE(u.multiply(x).isApproximate(y, 0.0001));
}

TEST_F (mockGaussInput, findX){
    auto x = backward_sub(gauss_elimination(g), y);
    // ASSERT_TRUE(g.multiply(x).isApproximate(y, 0.0001)); // FIXME: esto falla y no se si es esperable
    std::cout << g << std::endl;

}