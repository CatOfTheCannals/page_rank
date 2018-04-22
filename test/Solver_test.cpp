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

        v.setIndex(0, 0,1);
        v.setIndex(0, 1,1.14286);
        v.setIndex(0, 2,1.28571);
        v.setIndex(1, 0,0);
        v.setIndex(1, 1,1);
        v.setIndex(1, 2,2);
        v.setIndex(2, 0,0);
        v.setIndex(2, 1,0);
        v.setIndex(2, 2,1);

        y.setIndex(0, 0, 10);
        y.setIndex(1, 0, 20);
        y.setIndex(2, 0, 30);

        r.setIndex(0, 0, 10);
        r.setIndex(1, 0, 20);
        r.setIndex(2, 0, 30);
        r.setIndex(3, 0, 40);

        z.setIndex(0, 0,17.1431);
        z.setIndex(1, 0,-40);
        z.setIndex(2, 0,30);

        fourByFour.setIndex(0, 0, 3);
        fourByFour.setIndex(0, 1, 0);
        fourByFour.setIndex(0, 2, 4);
        fourByFour.setIndex(0, 3, 4);
        fourByFour.setIndex(1, 0, 0);
        fourByFour.setIndex(1, 1, 2);
        fourByFour.setIndex(1, 2, 0);
        fourByFour.setIndex(1, 3, 2);
        fourByFour.setIndex(2, 0, 1);
        fourByFour.setIndex(2, 1, 2);
        fourByFour.setIndex(2, 2, 0);
        fourByFour.setIndex(2, 3, 4);
        fourByFour.setIndex(3, 0, 2);
        fourByFour.setIndex(3, 1, 2);
        fourByFour.setIndex(3, 2, 2);
        fourByFour.setIndex(3, 3, 4);
    }
    Matrix g = Matrix(3,3);
    Matrix v = Matrix(3,3);
    Matrix y = Matrix(3,1);
    Matrix r = Matrix(4,1);
    Matrix z = Matrix(3,1);
    Matrix fourByFour = Matrix(4,4);
};

TEST_F (mockGaussInput, gaussElimFourByFour){
    /*
    Matrix l(fourByFour.rows(), fourByFour.cols());
    Matrix u(fourByFour.rows(), fourByFour.cols());
    std::tie(l, u) = gauss_elimination(fourByFour);

    std::cout << "l" << std::endl;
    std::cout << l << std::endl;

    std::cout << "u" << std::endl;
    std::cout << u << std::endl;

    std::cout << "lu" << std::endl;
    std::cout << l.multiply(u) << std::endl;

    std::cout << "original" << std::endl;
    std::cout << fourByFour << std::endl;

    std::cout << "difference" << std::endl;
    std::cout << fourByFour + l.multiply(u) * -1 << std::endl;

    ASSERT_TRUE(fourByFour.isApproximate(l.multiply(u), 0.0001));
    */
}

TEST_F (mockGaussInput, backwardSub){
    auto x = backward_sub(v, y);
    std::cout << x << std::endl;
    // ASSERT_TRUE(x.isApproximate(z, 0.0001)); // z la jarcodie en base a los resultados de solve_triangular de scipy
    // ASSERT_TRUE(v.multiply(x).isApproximate(y, 0.0001));
}
/*
TEST_F (mockGaussInput, forwardSub){
    auto vt = v.transpose();
    auto x = forward_sub(vt, y);
    ASSERT_TRUE(vt.multiply(x).isApproximate(y, 0.0001));
}



TEST_F (mockGaussInput, findX){

    Matrix p = Matrix::identity(3);
    p.swapRows(0, 2);
    p.swapRows(0, 1);

    Matrix l(fourByFour.rows(), fourByFour.cols());
    Matrix u(fourByFour.rows(), fourByFour.cols());
    std::tie(l, u) = gauss_elimination(fourByFour);
    auto q = forward_sub(l, r);
    auto x = backward_sub(u, q);

    std::cout << std::endl << l << std::endl;
    std::cout << u << std::endl;
    std::cout << l.multiply(u) << std::endl;
    std::cout << fourByFour << std::endl;
    std::cout << l.multiply(u) + fourByFour * -1 << std::endl;
    std::cout << x << std::endl;

    ASSERT_TRUE(fourByFour.multiply(x).isApproximate(r, 0.0001));

}*/