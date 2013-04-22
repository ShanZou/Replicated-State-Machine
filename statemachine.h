#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <string>
#include <boost/shared_ptr.hpp>

namespace mp2 {

class StateMachine {
public:
	// perform an operation on a state
	virtual std::string apply(const std::string &operation) = 0;
	// query the current state. Does not update the object!
 	virtual std::string getState(void) const = 0;
	// virtual destructor for proper interface semantics
	virtual ~StateMachine() {};
};

class StateMachineFactory {
public:
	// creates a new state machine initialized with the given parameter
	virtual boost::shared_ptr<StateMachine> make(const std::string &parameter) = 0;
	virtual ~StateMachineFactory() {};
};

template<class stateMachineClass>
class SimpleStateMachineFactory : public StateMachineFactory {
public:
	virtual boost::shared_ptr<StateMachine> make (const std::string &parameter) {
		return boost::shared_ptr<stateMachineClass>(new stateMachineClass(parameter));
	}
};

} // namespace

#endif

