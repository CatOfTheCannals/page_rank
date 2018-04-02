#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gtest/gtest.h"

#include "../src/Matrix.hpp"

// --------- SET UP --------------
class mockMatrices : public ::testing::Test {
protected:
    virtual void SetUp() {

        e.setIndex(0, 1, 4);
        e.setIndex(0, 2, 5);
        e.setIndex(0, 0, 6);
        e.setIndex(1, 1, 1);
        e.setIndex(1, 2, 2);
        e.setIndex(1, 0, 3);
        e.setIndex(2, 1, 4);
        e.setIndex(2, 2, 5);
        e.setIndex(2, 0, 6);
        e.setIndex(3, 1, 7);
        e.setIndex(3, 2, 8);
        e.setIndex(3, 0, 9);
        e.setIndex(4, 1, 1);
        e.setIndex(4, 2, 2);
        e.setIndex(4, 0, 3);

        m.setIndex(1, 1, 1);
        m.setIndex(1, 2, 2);
        m.setIndex(1, 0, 0);
        m.setIndex(2, 1, 4);
        m.setIndex(2, 2, 5);
        m.setIndex(2, 0, 6);
        m.setIndex(0, 1, 7);
        m.setIndex(0, 2, 8);
        m.setIndex(0, 0, 9);

        l.setIndex(1, 1, 1);
        l.setIndex(1, 2, 1);
        l.setIndex(1, 0, 1);
        l.setIndex(2, 1, 1);
        l.setIndex(2, 2, 1);
        l.setIndex(2, 0, 1);
        l.setIndex(0, 1, -8);
        l.setIndex(0, 2, 1);
        l.setIndex(0, 0, 1);


        std::cout << "Test Matrix initialized:" << std::endl;
        std::cout << "e:" << std::endl;
        std::cout << e << std::endl;
        /*
        std::cout << "m:" << std::endl;
        std::cout << m << std::endl;
        std::cout << "l:" << std::endl;
        std::cout << l << std::endl;
        */
    }
    Matrix e = Matrix(5,3);
    Matrix m = Matrix(3,3);
    Matrix l = Matrix(3,3);
};

TEST_F (mockMatrices, getIndex){
        ASSERT_EQ(1, e(1,1));
}

TEST_F (mockMatrices, copyConstructor){

    Matrix e_copy(e);
    for (std::size_t i = 0; i < e.rows(); i++) {
        for (std::size_t j = 0; j < e.cols(); j++) {
            ASSERT_EQ(e_copy(i, j), e(i, j));
        }
    }

}

TEST_F (mockMatrices, sumOperator){
    auto e_copy = e;
    e + e_copy;
    for (std::size_t i = 0; i < e.rows(); i++) {
        for (std::size_t j = 0; j < e.cols(); j++) {
            ASSERT_EQ(e_copy(i, j) * 2,  e(i, j));
        }
    }
}

TEST_F (mockMatrices, getRow){
    int rows, cols;
    std::tie(rows, cols) = e.shape();
    for (std::size_t i = 0; i < e.rows(); i++) {
        auto e_row = e.getRow(i);
        for (std::size_t j = 0; j < e.cols(); j++) {
            ASSERT_EQ(e_row(j),  e(i, j));
        }
    }
}


TEST_F (mockMatrices, shape){
    int rows, cols;
    std::tie(rows, cols) = e.shape();
    ASSERT_EQ(rows, e.rows());
    ASSERT_EQ(cols, e.cols());

}

TEST_F (mockMatrices, equality){
    auto e_copy = e;
    ASSERT_EQ(e_copy , e);
}

TEST_F (mockMatrices, swapRows){
    int i1 = 0;
    int i2 = 4;
    auto e_row_1 = e.getRow(i1);
    auto e_row_2 = e.getRow(i2);
    e.swapRows(i1, i2);
    ASSERT_EQ(e_row_1, e.getRow(i2));
    ASSERT_EQ(e_row_2, e.getRow(i1));
}