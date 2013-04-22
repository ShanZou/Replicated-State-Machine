#ifndef REPLICAS_H
#define REPLICAS_H

#include <boost/shared_ptr.hpp>
#include <vector>

#include "Replica.h"

namespace mp2 {

/* this class is used to contact other replicas. 
Usage is simple: replicas[i].apply(...) */
class Replicas {
private:
	std::string pipedir;
	unsigned int numreplicas;
	std::vector<boost::shared_ptr<ReplicaClient> > replicas;
	std::string pipe_path(unsigned int id) const;
	bool threadPool;

public:
	Replicas(int argc, char **argv, unsigned int * myid = NULL);

	ReplicaIf & operator [](unsigned int);

	unsigned int numReplicas() const { return numreplicas;}

	// start a server with the given replica handler and id
	void serve(boost::shared_ptr<ReplicaIf> replica, unsigned int id);
};

} // namespace

#endif