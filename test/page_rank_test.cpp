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

        for(int j = 0; j < 5; j ++){
            double sum = 0;
            for(int i = 0; i < 5; i ++){
                sum += W(i,j);
            }
            if(sum != 0){
                C.setIndex(j,j,1/sum);
            }
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


};

TEST_F (pageRankTest, test_aleatorio){
    std::cout << W << std::endl;
    std::cout << C << std::endl;

    double p = 0.85;

    ASSERT_TRUE(page_rank(W, C, p).isApproximate(test_aleatorio_out, 0.0001));
}