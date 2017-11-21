#include <gtest/gtest.h>

#include "../../lib/structures/segment_tree.hpp"

/**
 *  SegmentTree fixture.
 */
class SegmentTreeTest : public ::testing::Test {
    SegmentTree<double> sm_tree;

    void SetUp() override {}
};

TEST_F(SegmentTreeTest, SampleTest) { EXPECT_EQ(0, 0); }
