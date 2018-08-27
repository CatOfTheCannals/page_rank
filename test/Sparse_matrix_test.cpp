#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gtest/gtest.h"

#include "../src/Sparse_matrix_vom.hpp"

// --------- SET UP --------------
class mockSparseMatrices : public ::testing::Test {
protected:
    virtual void SetUp() {


        e.setIndex(5, 3, 6);
        e.setIndex(5, 1, 4);
        e.setIndex(5, 2, 5);
        e.setIndex(1, 3, 3);
        e.setIndex(1, 1, 1);
        e.setIndex(1, 2, 2);
        e.setIndex(2, 3, 6);
        e.setIndex(2, 1, 4);
        e.setIndex(2, 2, 5);
        e.setIndex(3, 3, 9);
        e.setIndex(3, 1, 7);
        e.setIndex(3, 2, 8);
        e.setIndex(4, 3, 3);
        e.setIndex(4, 1, 1);
        e.setIndex(4, 2, 2);

        m.setIndex(1, 1, 1);
        m.setIndex(1, 2, 2);
        m.setIndex(1, 3, 3);
        m.setIndex(2, 1, 4);
        m.setIndex(2, 2, 3);
        m.setIndex(2, 3, 6);
        m.setIndex(3, 1, 7);
        m.setIndex(3, 2, 8);
        m.setIndex(3, 3, 9);

        l.setIndex(1, 1, 1);
        l.setIndex(1, 2, 1);
        l.setIndex(1, 3, 1);
        l.setIndex(2, 1, 1);
        l.setIndex(2, 2, 1);
        l.setIndex(2, 3, 1);
        l.setIndex(3, 1, -8);
        l.setIndex(3, 2, 1);
        l.setIndex(3, 3, 1);
/*
        g.setIndex(3, 3, 1);
        g.setIndex(3, 1, 2);
        g.setIndex(3, 2, 3);
        g.setIndex(1, 1, 4);
        g.setIndex(1, 2, 3);
        g.setIndex(1, 3, 6);
        g.setIndex(2, 1, 7);
        g.setIndex(2, 2, 8);
        g.setIndex(2, 3, 9);
*/

        /*
        std::cout << "Test Sparse_matrix_vom initialized:" << std::endl;
        std::cout << "e:" << std::endl;
        std::cout << e << std::endl;
        std::cout << "m:" << std::endl;
        std::cout << m << std::endl;
        std::cout << "l:" << std::endl;
        std::cout << l << std::endl;
        */
    }


    Sparse_matrix_vom e = Sparse_matrix_vom(5,3);
    Sparse_matrix_vom m = Sparse_matrix_vom(3,3);
    Sparse_matrix_vom l = Sparse_matrix_vom(3,3);
    Sparse_matrix_vom g = Sparse_matrix_vom(3,3);

};



TEST_F (mockSparseMatrices, getIndex){

    g.setIndex(1, 1, 7);
    ASSERT_EQ(7, g(1,1));
    g.setIndex(1, 1, 0.00000001);
    ASSERT_EQ(0, g(1,1));
}

TEST_F (mockSparseMatrices, copyConstructor){

    Sparse_matrix_vom e_copy(e);
    for (std::size_t i = 1; i < e.rows(); i++) {
        for (std::size_t j = 1; j < e.cols(); j++) {
            ASSERT_EQ(e_copy(i, j), e(i, j));
        }
    }

}
/*
TEST_F (mockSparseMatrices, transpose){

    auto t = e.transpose();

    for (std::size_t i = 1; i < e.rows(); i++) {
        for (std::size_t j = 1; j < e.cols(); j++) {
            ASSERT_EQ(t(i, j), e(j, i));
        }
    }
}
*/
TEST_F (mockSparseMatrices, sumAndScalarOperator){
    auto e_copy = e;
    auto duplicated = e * 2;
    auto sum = e + e_copy;
    ASSERT_EQ(duplicated, sum);
}

TEST_F (mockSparseMatrices, equality){
    auto e_copy = e;
    ASSERT_EQ(e_copy , e);
}

TEST_F (mockSparseMatrices, swapRows){
    int i1 = 1;
    int i2 = 4;
    auto e_row_1 = e.getRow(i1);
    auto e_row_2 = e.getRow(i2);
    e.swapRows(i1, i2);
    ASSERT_EQ(e_row_1, e.getRow(i2));
    ASSERT_EQ(e_row_2, e.getRow(i1));
}

TEST_F (mockSparseMatrices, subMatrix){ // FIXME: este test solo checkea que la funcion subSparse_matrix_vom obtiene rows adecuadamente
    for (std::size_t i = 1; i < e.rows(); i++) {
        auto e_row = e.getRow(i);
        auto e_sub = e.subMatrix(i,i,1, e.cols());
        ASSERT_EQ(e_row, e_sub);
    }
}

TEST_F (mockSparseMatrices, Sparse_matrix_matmul){
    Sparse_matrix_vom r = e.multiply(m);
    ASSERT_EQ(r.rows(),e.rows()); //TODO: check if the test ends with this assertion
    ASSERT_EQ(r.cols(),m.cols());
    //ASSERT_EQ(9*6+5+6,r(1,1)); //TODO:check if this possition is calculated correctly.
    ASSERT_EQ(3*7+1+8,r(1,1));

    Sparse_matrix_vom id = Sparse_matrix_vom::identity(m.rows());

    ASSERT_EQ(m, m.multiply(id));
}


TEST_F (mockSparseMatrices, maxCoeff){
    int x;
    int y;
    std::tie(x, y) = e.maxCoeff();

    ASSERT_EQ(3, x);
    ASSERT_EQ(3, y);
}

TEST_F (mockSparseMatrices, abs){
    Sparse_matrix_vom l_copy(l);
    l_copy.setIndex(3, 1, 8);
    ASSERT_EQ(l_copy, l.abs());
}