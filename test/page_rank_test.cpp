#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "gtest/gtest.h"
#include "../src/page_rank.h"

// --------- SET UP --------------
class pageRankTest : public ::testing::Test {
protected:
    virtual void SetUp() {

        W.setIndex(0,2,1);
        W.setIndex(0,3,1);
        W.setIndex(0,4,1);
        W.setIndex(1,0,1);
        W.setIndex(1,3,1);
        W.setIndex(1,4,1);
        W.setIndex(2,0,1);
        W.setIndex(2,3,1);
        W.setIndex(2,4,1);
        W.setIndex(3,0,1);
        W.setIndex(3,2,1);
        W.setIndex(3,4,1);

        /*
        W.setIndex(2,0,1);
        W.setIndex(3,0,1);
        W.setIndex(4,0,1);
        W.setIndex(0,1,1);
        W.setIndex(3,1,1);
        W.setIndex(4,1,1);
        W.setIndex(0,2,1);
        W.setIndex(3,2,1);
        W.setIndex(4,2,1);
        W.setIndex(0,3,1);
        W.setIndex(2,3,1);
        W.setIndex(4,3,1);
        */


        for(int i = 0; i < 5; i++) { //fill cyclic matrix
            std::cout << i % 5 << " " << (i + 1) % 5 << std::endl;
            ciclic.setIndex(i % 5,(i + 1) % 5,1);
        }

        test_aleatorio_out.setIndex(0,0,0.219302);
        test_aleatorio_out.setIndex(1,0,0.0778443);
        test_aleatorio_out.setIndex(2,0,0.202115);
        test_aleatorio_out.setIndex(3,0,0.219302);
        test_aleatorio_out.setIndex(4,0,0.281437);
    }

    Matrix test_aleatorio_out = Matrix(5,1);
    Matrix W = Matrix(5,5);
    Matrix C = Matrix(5,5);

    Matrix ciclic = Matrix(5,5);

};

TEST_F (pageRankTest, test_aleatorio){

    double p = 0.85;

    Matrix C = colSumDiag(W);

    page_rank(W, C, p);

    ASSERT_TRUE(page_rank(W, C, p).isApproximate(test_aleatorio_out, 0.0001));
}

TEST_F (pageRankTest, ciclicMatrix){
    double p = 0.85;

    Matrix C = colSumDiag(ciclic);

    // std::cout << page_rank(ciclic, C, p) << std::endl;
}