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

TEST_F (pageRankTest, test_aleatorio){

    double p = 0.85;

    Sparse_matrix_2 C = colSumDiag(W);

    // std::cout << page_rank(W, C, p) << std::endl;

    ASSERT_TRUE (page_rank(W, C, p).isApproximate(test_aleatorio_out));
}

TEST_F (pageRankTest, ciclicSparse_matrix_2){
    double p = 0.85;

    Sparse_matrix_2 C = colSumDiag(ciclic);

    std::cout << "ciclic: " << std::endl << ciclic << std::endl;

    std::cout << page_rank(ciclic, C, p) << std::endl;
}
