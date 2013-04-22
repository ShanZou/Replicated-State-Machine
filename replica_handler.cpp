#include "replica_handler.h"

using namespace mp2;
using namespace std;

#include <cstdlib>
#include <iostream>

Replica::Replica(int myid, StateMachineFactory & factory, Replicas & replicas) 
: factory(factory), id(myid), replicas(replicas) {
	// any initialization you need goes here
}

void Replica::checkExists(const string &name) const throw (ReplicaError) {
	if (machines.find(name) == machines.end()) {
		ReplicaError error;
		error.type = ErrorType::NOT_FOUND;
		error.name = name;
		error.message = string("Cannot find machine ") + name;
		throw error;
	}	
}

void Replica::create(const string & name, const string & initialState) {
	if (machines.find(name) != machines.end()) {
		ReplicaError error;
		error.type = ErrorType::ALREADY_EXISTS;
		error.name = name;
		error.message = string("Machine ") + name + (" already exists");
		throw error;
	}
 	machines.insert(make_pair(name, factory.make(initialState)));
}

void Replica::apply(string & result, const string & name, const string& operation) {
	checkExists(name);
	result = machines[name]->apply(operation);
}

void Replica::getState(string& result, const string &name) {
	checkExists(name);

	result = machines[name]->getState();
}

void Replica::remove(const string &name) {
	checkExists(name);

	machines.erase(name);
}


/* DO NOT CHANGE THIS */
void Replica::exit(void) {
	clog << "Replica " << id << " exiting" << endl;
	::std::exit(0);	// no return
}

