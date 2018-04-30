#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "../src/Sparse_solvers.hpp"


// --------- SET UP --------------
class sMockGaussInput : public ::testing::Test {
protected:
    virtual void SetUp() {
            g.setIndex(1, 1, 1);
            g.setIndex(1, 2, 2);
            g.setIndex(1, 3, 3);
            g.setIndex(2, 1, 4);
            g.setIndex(2, 2, 5);
            g.setIndex(2, 3, 6);
            g.setIndex(3, 1, 7);
            g.setIndex(3, 2, 8);
            g.setIndex(3, 3, 9);

            v.setIndex(1, 1,1);
            v.setIndex(1, 2,1.14286);
            v.setIndex(1, 3,1.28571);
            v.setIndex(2, 1,0);
            v.setIndex(2, 2,1);
            v.setIndex(2, 3,2);
            v.setIndex(3, 1,0);
            v.setIndex(3, 2,0);
            v.setIndex(3, 3,1);

            y.setIndex(1, 1, 10);
            y.setIndex(2, 1, 20);
            y.setIndex(3, 1, 30);

            r.setIndex(1, 1, 10);
            r.setIndex(2, 1, 20);
            r.setIndex(3, 1, 30);
            r.setIndex(4, 1, 40);

            z.setIndex(1, 1,17.1431);
            z.setIndex(2, 1,-40);
            z.setIndex(3, 1,30);

            fourByFour.setIndex(1, 1, 3);
            fourByFour.setIndex(1, 2, 0);
            fourByFour.setIndex(1, 3, 4);
            fourByFour.setIndex(1, 4, 4);
            fourByFour.setIndex(2, 1, 0);
            fourByFour.setIndex(2, 2, 2);
            fourByFour.setIndex(2, 3, 0);
            fourByFour.setIndex(2, 4, 2);
            fourByFour.setIndex(3, 1, 1);
            fourByFour.setIndex(3, 2, 2);
            fourByFour.setIndex(3, 3, 0);
            fourByFour.setIndex(3, 4, 4);
            fourByFour.setIndex(4, 1, 2);
            fourByFour.setIndex(4, 2, 2);
            fourByFour.setIndex(4, 3, 2);
            fourByFour.setIndex(4, 4, 4);
    }
    Sparse_matrix_2 g = Sparse_matrix_2(3,3);
    Sparse_matrix_2 v = Sparse_matrix_2(3,3);
    Sparse_matrix_2 y = Sparse_matrix_2(3,1);
    Sparse_matrix_2 r = Sparse_matrix_2(4,1);
    Sparse_matrix_2 z = Sparse_matrix_2(3,1);
    Sparse_matrix_2 fourByFour = Sparse_matrix_2(4,4);
};


TEST_F (sMockGaussInput, gaussElimFourByFour){


        Sparse_matrix_2 l(fourByFour.rows(), fourByFour.cols());
        Sparse_matrix_2 u(fourByFour.rows(), fourByFour.cols());
        std::tie(l, u) = s_gauss_elimination(fourByFour);
/*
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
*/
        ASSERT_TRUE(fourByFour.isApproximate(l.multiply(u)));

}


TEST_F (sMockGaussInput, backwardSub){
    auto x = backward_sub(v, y);
    // ASSERT_TRUE(x.isApproximate(z, 0.0001)); // z la jarcodie en base a los resultados de solve_triangular de scipy
    ASSERT_TRUE(v.multiply(x).isApproximate(y));
}

TEST_F (sMockGaussInput, forwardSub){
    auto vt = v.transpose();
    auto x = forward_sub(vt, y);
    ASSERT_TRUE(vt.multiply(x).isApproximate(y));
}

TEST_F (sMockGaussInput, findX){

    Sparse_matrix_2 p = Sparse_matrix_2::identity(3);
    p.swapRows(0, 2);
    p.swapRows(0, 1);

    Sparse_matrix_2 l(fourByFour.rows(), fourByFour.cols());
    Sparse_matrix_2 u(fourByFour.rows(), fourByFour.cols());
    std::tie(l, u) = s_gauss_elimination(fourByFour);
    auto q = forward_sub(l, r);
    auto x = backward_sub(u, q);


ASSERT_TRUE(fourByFour.multiply(x).isApproximate(r));

}

