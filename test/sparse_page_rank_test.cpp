#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "../src/sparse_page_rank.h"

// --------- SET UP --------------
class pageRankTest : public ::testing::Test {
protected:
    virtual void SetUp() {

        W.setIndex(1,3,1);
        W.setIndex(1,4,1);
        W.setIndex(1,5,1);
        W.setIndex(2,1,1);
        W.setIndex(2,4,1);
        W.setIndex(2,5,1);
        W.setIndex(3,1,1);
        W.setIndex(3,4,1);
        W.setIndex(3,5,1);
        W.setIndex(4,1,1);
        W.setIndex(4,3,1);
        W.setIndex(4,5,1);

        for(int i = 1; i <= 5; i++) { //fill cyclic Sparse_matrix_2
            ciclic.setIndex((i % 5) + 1,((i + 1) % 5)+1,1);
        }

        test_aleatorio_out.setIndex(1,1,0.219302);
        test_aleatorio_out.setIndex(2,1,0.0778443);
        test_aleatorio_out.setIndex(3,1,0.202115);
        test_aleatorio_out.setIndex(4,1,0.219302);
        test_aleatorio_out.setIndex(5,1,0.281437);
    }

    Sparse_matrix_2 test_aleatorio_out = Sparse_matrix_2(5,1);
    Sparse_matrix_2 W = Sparse_matrix_2(5,5);
    Sparse_matrix_2 C = Sparse_matrix_2(5,5);

    Sparse_matrix_2 ciclic = Sparse_matrix_2(5,5);

};

/*
TEST_F (pageRankTest, test_aleatorio){

    double p = 0.85;

    Sparse_matrix_2 C = colSumDiag(W);

    std::cout << "output errors: " << page_rank(W, C, p) + test_aleatorio_out * (-1) << std::endl;
}

TEST_F (pageRankTest, ciclicSparse_matrix_2){
    double p = 0.85;

    Sparse_matrix_2 C = colSumDiag(ciclic);

    std::cout << "ciclic: " << std::endl << ciclic << std::endl;

    std::cout << page_rank(ciclic, C, p) << std::endl;
}*/

TEST_F (pageRankTest, random_gen_test){

    double p = 0.85;

    Sparse_matrix_2 W(Sparse_matrix_2::random_matrix(500, 500));

    Sparse_matrix_2 C = colSumDiag(W);

    Sparse_matrix_2 Cp = C * p;

    // page_rank(W, C, p);

    int i, j = 0;
    double val;

    auto begin = GET_TIME;
    Sparse_matrix_2 res(W.rows(), Cp.cols());
    Sparse_matrix_2 row(1,W.cols());
    Sparse_matrix_2 col(1,Cp.cols());
    auto end = GET_TIME;
    std::cout << "'create_stuff_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    begin = GET_TIME;
    bool if_guard = W._matrix.find(i) != W._matrix.end() && Cp._matrix.find(j) != Cp._matrix.end();
    end = GET_TIME;
    std::cout << "'if_guard_time': " << GET_TIME_DELTA(begin, end) << std::endl;


    if(if_guard) {
        begin = GET_TIME;
        row._matrix[1] = W._matrix.find(i)->second;
        col._matrix[1] = Cp._matrix.find(j)->second;
        end = GET_TIME;
        std::cout << "'get_row_and_col_time': " << GET_TIME_DELTA(begin, end) << std::endl;

        begin = GET_TIME;
        val = dotProd(row, col);
        end = GET_TIME;
        std::cout << "'dot_prod_time': " << GET_TIME_DELTA(begin, end) << std::endl;

    } else {
        val = 0;
    }

    begin = GET_TIME;
    res.setIndex(i, j, val);
    end = GET_TIME;
    std::cout << "'set_index_time': " << GET_TIME_DELTA(begin, end) << std::endl;

}