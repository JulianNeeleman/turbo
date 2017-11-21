#include <gtest/gtest.h>

#include "../../lib/geometry/point.hpp"

/**
 *  Point fixture.
 */
class PointTest : public ::testing::Test {
    void SetUp() override {}
};

TEST_F(PointTest, SampleTest) { EXPECT_EQ(0, 0); }
