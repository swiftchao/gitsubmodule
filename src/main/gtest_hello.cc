/*************************************************************************
    > File Name: gtest_hello.cc
    > Author: chaofei
    > Mail: chaofeibest@163.com 
    > Created Time: 2024-12-02 17:14:54
 ************************************************************************/

// test_math.cc
#include "gtest/gtest.h"
#include "include/math.h"
//#include "math.h"

// 测试用例：测试add函数是否能正确相加两个整数
TEST(AdditionTest, BasicAddition) 
{
    int result = add(3, 5);
    EXPECT_EQ(result, 8);
}

// 另一个测试用例：测试负数相加的情况
TEST(AdditionTest, NegativeNumbersAddition) 
{
    int result = add(-3, -5);
    EXPECT_EQ(result, -8);
}

TEST(SubtractTest, BasicSubtract)
{
    int result = subtract(5, 3);
    EXPECT_EQ(result, 2);
}

TEST(SubstractTest, NegativeNumbersSubtract)
{
    int result = subtract(-3, -5);
    EXPECT_EQ(result, 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

