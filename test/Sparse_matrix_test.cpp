#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "gtest/gtest.h"

#include "../src/Sparse_matrix.hpp"

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

        g.setIndex(3, 3, 1);
        g.setIndex(3, 1, 2);
        g.setIndex(3, 2, 3);
        g.setIndex(1, 1, 4);
        g.setIndex(1, 2, 3);
        g.setIndex(1, 3, 6);
        g.setIndex(2, 1, 7);
        g.setIndex(2, 2, 8);
        g.setIndex(2, 3, 9);

        /*
        std::cout << "Test Sparse_matrix initialized:" << std::endl;
        std::cout << "e:" << std::endl;
        std::cout << e << std::endl;
        std::cout << "m:" << std::endl;
        std::cout << m << std::endl;
        std::cout << "l:" << std::endl;
        std::cout << l << std::endl;
        */
    }

    Sparse_matrix e = Sparse_matrix(5,3);
    Sparse_matrix m = Sparse_matrix(3,3);
    Sparse_matrix l = Sparse_matrix(3,3);
    Sparse_matrix g = Sparse_matrix(3,3);
};

TEST_F (mockSparseMatrices, getIndex){
    ASSERT_EQ(1, e(1,1));
}

TEST_F (mockSparseMatrices, copyConstructor){

    Sparse_matrix e_copy(e);
    for (std::size_t i = 1; i < e.rows(); i++) {
        for (std::size_t j = 1; j < e.cols(); j++) {
            ASSERT_EQ(e_copy(i, j), e(i, j));
        }
    }

}

TEST_F (mockSparseMatrices, transpose){

    auto t = e.transpose();

    for (std::size_t i = 1; i < e.rows(); i++) {
        for (std::size_t j = 1; j < e.cols(); j++) {
            ASSERT_EQ(t(i, j), e(j, i));
        }
    }
}

TEST_F (mockSparseMatrices, sumAndScalarOperator){
    auto e_copy = e;
    auto duplicated = e * 2;
    auto sum = e + e_copy;
    ASSERT_EQ(e + e_copy, sum);
}


TEST_F (mockSparseMatrices, getRow){
    for (std::size_t i = 1; i < e.rows(); i++) {
        auto e_row = e.getRow(i);
        for (std::size_t j = 1; j < e.cols(); j++) {
            ASSERT_EQ(e_row(j),  e(i, j));
        }
    }
}
/*
TEST_F (mockSparseMatrices, shape){
    int rows, cols;
    std::tie(rows, cols) = e.shape();
    ASSERT_EQ(rows, e.rows());
    ASSERT_EQ(cols, e.cols());

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

TEST_F (mockSparseMatrices, subSparse_matrixRows){ // FIXME: este test solo checkea que la funcion subSparse_matrix obtiene rows adecuadamente
    int rows, cols;
    std::tie(rows, cols) = e.shape();
    for (std::size_t i = 1; i < e.rows(); i++) {
        auto e_row = e.getRow(i);
        auto e_sub = e.subMatrix(i,i,1, cols-1);
        ASSERT_EQ(e_row, e_sub);
    }
}

TEST_F (mockSparseMatrices, Sparse_matrixMultipOperator){
    Sparse_matrix r = e.multiply(m);
    ASSERT_EQ(r.rows(),e.rows()); //TODO: check if the test ends with this assertion
    ASSERT_EQ(r.cols(),m.cols());
    //ASSERT_EQ(9*6+5+6,r(1,1)); //TODO:check if this possition is calculated correctly.
    ASSERT_EQ(3*7+1+8,r(1,1));

    int rows, cols;
    std::tie(rows, cols) = m.shape();
    Sparse_matrix id = Sparse_matrix::identity(rows);
    ASSERT_EQ(m, m.multiply(id));
}


TEST_F (mockSparseMatrices, maxCoeff){
    int x = std::get<1>(e.maxCoeff());
    int y = std::get<1>(e.maxCoeff());
    ASSERT_EQ(3, x);
    ASSERT_EQ(1, y);
}

TEST_F (mockSparseMatrices, abs){
    Sparse_matrix l_copy(l);
    l_copy.setIndex(1, 1, 8);
    ASSERT_EQ(l_copy, l.abs());
}

*/