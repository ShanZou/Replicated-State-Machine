#include "frontend.h"
#include "replicas.h"

#include <iostream>

using namespace mp2;
using namespace std;
using boost::shared_ptr;

int main(int argc, char **argv) {
	shared_ptr<Replicas> replicas(new Replicas(argc, argv));

	FrontEnd frontEnd(replicas);


	try {
		shared_ptr<StateMachine> machine = frontEnd.create("testmachine", "initstate");

		cout << machine->getState() << endl;

		cout << machine->apply("testop") << endl;

		//cout << machine->getState() << endl;


		//frontEnd.remove("testmachine");

	} catch (ReplicaError e) {
			cerr << e.message << endl;
			return 1;
	}

	FrontEnd frontEnd2(replicas);

	try {
		shared_ptr<StateMachine> machine = frontEnd2.get("testmachine");

		cout << machine->getState() << endl;



		//frontEnd.remove("testmachine");

	} catch (ReplicaError e) {
			cerr << e.message << endl;
			return 1;
	}




	return 0;
}
