#ifndef __FRONTEND_H__
#define __FRONTEND_H__

#include <string>
#include <boost/shared_ptr.hpp>
#include <map>

#include "statemachine.h"
#include "replicas.h"


namespace mp2 {

struct Record
{
	int r1 , r2 , r3;
    Record()
    {
        r1 = r2 = r3 = -1;
    }
};
//extern std::map<std::string , Record> mymap;

class FrontEnd
{
	boost::shared_ptr<Replicas> replicas;

	static int numOfReplicas;
	static int cnt;					// number of state machine created
	static std::map<std::string , Record> mymap;

public:
	FrontEnd(boost::shared_ptr<Replicas> replicas);
	~FrontEnd();

	// create a new StateMachine and return a stub
	boost::shared_ptr<StateMachine> create(const std::string &name, const std::string &initState = "");
	// get a stub for an already created state machine;
	// returns NULL if it hasn't been created
	boost::shared_ptr<StateMachine> get(const std::string &name);
	// delete an existing state machine. Note: any remaining stubs for 
	// the state machine must throw an exception when apply() or getState() 
	// are called
	void remove(const std::string &name);
	static std::map<std::string , Record> getMap();

};

} // namespace

#endif

