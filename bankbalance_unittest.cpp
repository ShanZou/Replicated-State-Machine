#include "bankbalance.h"
#include <gtest/gtest.h>

using namespace mp2;
using namespace std;

TEST(BankBalanceTest, Constructor) {
	BankBalance b0("0"), b1("1"), bbig("12345678"), bneg("-1");
	EXPECT_EQ(b0.getState(), string("0"));
	EXPECT_EQ(b1.getState(), string("1"));
	EXPECT_EQ(bbig.getState(), string("12345678"));
	EXPECT_EQ(bneg.getState(), string("-1"));
}

TEST(BankBalanceTest, Apply) {
	BankBalance b("0");

	EXPECT_EQ(b.apply("0"), string("0"));
	EXPECT_EQ(b.getState(), string("0"));
	EXPECT_EQ(b.apply("1"), string("1"));
	EXPECT_EQ(b.getState(), string("1"));
	EXPECT_EQ(b.apply("12345678"), string("12345679"));
	EXPECT_EQ(b.getState(), string("12345679"));
	EXPECT_EQ(b.apply("-10000000"), string("2345679"));
	EXPECT_EQ(b.getState(), string("2345679"));
	EXPECT_EQ(b.apply("-2345680"), string("-1"));
	EXPECT_EQ(b.getState(), string("-1"));
}