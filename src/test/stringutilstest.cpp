#include "../BackTester/stringutils.h"
#include "gtest/gtest.h"
#include <vector>

TEST (StringUtils, SplitSimpleWords) {
    std::string s("what,have,we,here");
    auto v = StringUtils::Split(s);
    EXPECT_EQ(v[0], "what");
    EXPECT_EQ(v[1], "have");
    EXPECT_EQ(v[2], "we");
    EXPECT_EQ(v[3], "here");
}

TEST (StringUtils, SplitWithSequencialCommas) {
    std::string s("what,,have,we,,here");
    auto v = StringUtils::Split(s);
    EXPECT_EQ(v[0], "what");
    EXPECT_EQ(v[1], "");
    EXPECT_EQ(v[2], "have");
    EXPECT_EQ(v[3], "we");
    EXPECT_EQ(v[4], "");
    EXPECT_EQ(v[5], "here");
}

TEST (StringUtils, splitWithNumbers) {
    std::string s("what,193.0,2039.433,904,1");
    auto v = StringUtils::Split(s);
    EXPECT_EQ(v[0], "what");
    EXPECT_EQ(v[1], "193.0");
    EXPECT_EQ(v[2], "2039.433");
    EXPECT_EQ(v[3], "904");
    EXPECT_EQ(v[4], "1");
}

