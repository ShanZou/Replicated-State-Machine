#include <string>

#include "stringmachine.h"

#include "gtest/gtest.h"

using namespace std;
using namespace mp2;

TEST(StringMachineTest, Functionality) {
	string s1 = "Initial state";
	string s2 = "State #2";
	string s3 = "State #3";
	StringMachine machine(s1);

	EXPECT_EQ(machine.getState(), s1);
	machine.apply(s2);
	EXPECT_EQ(machine.getState(), s2);
	machine.apply(s3);
	EXPECT_EQ(machine.getState(), s3);
}

TEST(StringMachineFactoryTest, Basic) {
	string s1 = "Initial state";
	SimpleStateMachineFactory<StringMachine> factory;

	boost::shared_ptr<StateMachine> machine = factory.make(s1);
	EXPECT_EQ(machine->getState(), s1);
}
