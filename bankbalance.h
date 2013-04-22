#ifndef BANKBALANCE_H
#define BANKBALANCE_H

#include "statemachine.h"

#include <sstream>
#include <boost/lexical_cast.hpp>

namespace mp2 {

class BankBalance : public StateMachine {
private:
	int balance; // can be negative in our implementation
public:
	// create with an initial balance
	BankBalance(const std::string & balanceStr) 
		: balance(boost::lexical_cast<int>(balanceStr)) {}

	// getState returns the balance as a string
	std::string getState() const {
		return boost::lexical_cast<std::string>(balance);
	}
	// apply takes an integer (possibly negative) to be added to the balance
	// returns current value
	std::string apply(const std::string & operation) {
		balance += boost::lexical_cast<int>(operation);
		return getState();
	}
};

typedef SimpleStateMachineFactory<BankBalance> BankBalanceFactory;

} // namespace

#endif