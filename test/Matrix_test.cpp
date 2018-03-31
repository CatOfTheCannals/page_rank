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
        e.setIndex(0, 3, 6);
        e.setIndex(1, 1, 1);
        e.setIndex(1, 2, 2);
        e.setIndex(1, 3, 3);
        e.setIndex(2, 1, 4);
        e.setIndex(2, 2, 5);
        e.setIndex(2, 3, 6);
        e.setIndex(3, 1, 7);
        e.setIndex(3, 2, 8);
        e.setIndex(3, 3, 9);
        e.setIndex(4, 1, 1);
        e.setIndex(4, 2, 2);
        e.setIndex(4, 3, 3);

        std::cout << "Test Matrix initialized:" << std::endl;
        std::cout << e << std::endl;

    }
    Matrix e = Matrix(5,3);
};

TEST_F (mockMatrices, getIndex){

        ASSERT_EQ(1, e(1,1));

}