#include <gtest/gtest.h>
#include "game.hpp"
#include "GameObject.hpp"

TEST(CheckColisions, Test1) {
    GameObject carX(0, 0, 2, 1, "X");
    GameObject car1(4, 0, 1, 2, "1");
    GameObject car2(2, 2, 3, 1, "2");
    std::vector<GameObject> cars = {carX, car1, car2};
    
    EXPECT_EQ(checkColisions(cars), false);
}


int test() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}