/* We use stringmachine to test replicas */
#include "replica_handler.h"
#include "stringmachine.h"
#include "gtest/gtest.h"

using namespace mp2;
using namespace std;

class ReplicaTest : public ::testing::Test {
protected:
	StringMachineFactory factory;
	Replica empty_1;
	Replica oneSM_2;

	static const string sm2_name;
	static const string sm2_initstate;
	static const string sm2_op;

	ReplicaTest() : empty_1(1, factory), oneSM_2(2, factory) {}

	virtual void SetUp() {
		oneSM_2.create(sm2_name, sm2_initstate);
	}
};

const string ReplicaTest::sm2_name = "machine name";
const string ReplicaTest::sm2_initstate = "initial state";
const string ReplicaTest::sm2_op = "operation";


TEST_F(ReplicaTest, Constructor) {
	// check to see if the constructors set the IDs OK
	EXPECT_EQ(empty_1.id, 1);
	EXPECT_EQ(oneSM_2.id, 2);
}

TEST_F(ReplicaTest, NotFound) {
	string result;
	EXPECT_THROW(empty_1.apply(result, sm2_name, sm2_op), ReplicaError);
	EXPECT_THROW(empty_1.getState(result, sm2_name), ReplicaError);
	EXPECT_THROW(empty_1.remove(sm2_name), ReplicaError);
}

TEST_F(ReplicaTest, ReCreateError) {
	EXPECT_THROW(oneSM_2.create(sm2_name, sm2_initstate), ReplicaError);
}

TEST_F(ReplicaTest, Create) {
	string result;

	oneSM_2.getState(result, sm2_name);
	EXPECT_EQ(result, sm2_initstate);
}

TEST_F(ReplicaTest, Apply) {
	string result;

	oneSM_2.apply(result, sm2_name, sm2_op);
	EXPECT_EQ(result, sm2_op);

	string result2;
	oneSM_2.getState(result2, sm2_name);
	EXPECT_EQ(result2, sm2_op);
}

TEST_F(ReplicaTest, Remove) {
	string result;
	oneSM_2.remove(sm2_name);
	EXPECT_THROW(oneSM_2.getState(result, sm2_name), ReplicaError);
}

typedef ReplicaTest ReplicaDeathTest;

TEST_F(ReplicaDeathTest, Exit) {
	EXPECT_EXIT(empty_1.exit(), ::testing::ExitedWithCode(0), "Replica 1 exiting");
}
