#include <gtest/gtest.h>

#include "matrix.h"


TEST(TestMatrix, Empty) {
    Matrix<int, 0> m;

    ASSERT_EQ(m.size(), 0);
    ASSERT_EQ(m[0][0], 0);
}

TEST(TestMatrix, SetValue) {
    Matrix<int, 0> m;
    m[0][0] = 2;
    
    ASSERT_EQ(m[0][0], 2);
}

TEST(TestMatrix, MultiplySetValue) {
    Matrix<int, 0> m;
    (m[0][0] = 1) = 2;

    ASSERT_EQ(m[0][0], 2);
}

TEST(TestMatrix, IteratorUnpack) {
    Matrix<int, 0> m;
    m[0][0] = 2;
    
    int x, y, z;
    auto it = m.begin();
    std::tie(x, y, z) = (*it);
    
    ASSERT_EQ(x, 0);
    ASSERT_EQ(y, 0);
    ASSERT_EQ(z, 2);
}


int main(int argc, char**argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
