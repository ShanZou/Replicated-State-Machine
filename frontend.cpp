#include "frontend.h"
#include <boost/shared_ptr.hpp>
#include "statemachine.h"
#include <iostream>

using namespace std;
using namespace mp2;
using boost::shared_ptr;

std::map<std::string , Record> FrontEnd::mymap;
int FrontEnd::numOfReplicas = 0;
int FrontEnd::cnt = 0;

class StateMachineStub : public mp2::StateMachine {
private:
	ReplicaIf & replica;
	const string name;

public:
	StateMachineStub(ReplicaIf & replica, const string &name)
		: replica(replica), name(name) {}
	virtual string apply(const string & operation) {
		string result;
		replica.apply(result, name, operation);
		return result;
	}

	virtual string getState(void) const {
		string result;
		replica.getState(result, name);
		return result;
	}
};
//std::map<std::string , Record> mymap;
FrontEnd::FrontEnd(boost::shared_ptr<Replicas> replicas) : replicas(replicas) {
	numOfReplicas = replicas -> numReplicas();
	cout << numOfReplicas << endl; //test
}

FrontEnd::~FrontEnd() { }

shared_ptr<StateMachine> FrontEnd::create(const string &name, const string &initialState) {
	Record rcd;

	(*replicas)[cnt % numOfReplicas].create(name, initialState);					// create new statemachine on different replicas
    rcd.r1 = cnt % numOfReplicas;

    if((cnt+1)%numOfReplicas != cnt % numOfReplicas)
    {
	    (*replicas)[(cnt+1) % numOfReplicas].create(name, initialState);
	    rcd.r2 = (cnt+1) % numOfReplicas;
    }

    if((cnt+2)%numOfReplicas != cnt % numOfReplicas)
    {
	    (*replicas)[(cnt+2) % numOfReplicas].create(name, initialState);				// for each statemachine, create 3 replica copies
	    rcd.r3 = (cnt+2) % numOfReplicas;												
    }


	mymap[name] = rcd;																// record the mapping in data structure mymap

	cnt ++;																			// increment the cnt.
	return get(name);
}

shared_ptr<StateMachine> FrontEnd::get(const string &name) {
	Record num = mymap[name];
	shared_ptr<StateMachine> result(new StateMachineStub((*replicas)[num.r1], name));
	return result;
}

void FrontEnd::remove(const string &name) {
	Record num = mymap[name];
	(*replicas)[num.r1].remove(name);
}


