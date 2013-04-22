#ifndef __STRINGMACHINE_H__
#define __STRINGMACHINE_H__

#include <string>

#include "statemachine.h"

namespace mp2 {

class StringMachine : public StateMachine {
private:
	std::string state;
public:
	StringMachine(const std::string & initialState) : state(initialState) {}

	virtual std::string apply(const std::string &operation) {
		state = operation;
		return state;
	}

	virtual std::string getState(void) const {
		return state;
	}
};

typedef SimpleStateMachineFactory<StringMachine> StringMachineFactory;

}

#endif