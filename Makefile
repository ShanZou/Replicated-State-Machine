GTEST_DIR=/class/ece428/libs/gtest-1.6.0
THRIFT_DIR=/class/ece428/libs
THRIFT=$(THRIFT_DIR)/bin/thrift
CFLAGS=-I./gen-cpp -g
CXXFLAGS=-I./gen-cpp -I$(GTEST_DIR)/include -I$(THRIFT_DIR)/include/thrift -I$(THRIFT_DIR)/include -Wall -Wextra -g
SRCS:=$(wildcard *.cpp)

TESTS:=$(patsubst %.cpp,%,$(wildcard *_unittest.cpp))
RPCSOURCES = gen-cpp/replica_constants.cpp gen-cpp/replica_types.cpp gen-cpp/Replica.cpp
RPCHEADERS := $(patsubst %.cpp,%.h,$(RPCSOURCES))
RPCOBJS := $(patsubst %.cpp,%.o,$(RPCSOURCES))
LDFLAGS=-L$(THRIFT_DIR)/lib -lpthread -lthrift -lboost_program_options-mt -lboost_filesystem-mt -lboost_system-mt

.PHONY: all test clean
all: replica client

replica: replica_handler.o replica_main.o replicas.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

client: client.o frontend.o replicas.o $(RPCOBJS)
	$(CXX) $(CXXFLAGS)  $^ $(LDFLAGS) -o $@

test: $(TESTS)
	@for test in $(TESTS) ; do \
		./$$test ; \
	done

.PHONY: thrift
thrift: 
	$(THRIFT) -gen cpp replica.thrift

$(RPCSOURCES) $(RPCHEADERS): replica.thrift
	$(THRIFT) -gen cpp $^

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


stringmachine_unittest: stringmachine_unittest.o gtest_main.a
	$(CXX) $(CXXFLAGS) -lpthread $^ -o $@

replicas_unittest: replicas_unittest.o replica_handler.o gtest_main.a
	$(CXX) $(CXXFLAGS) -lpthread $^ -o $@

bankbalance_unittest: bankbalance_unittest.o gtest_main.a
	$(CXX) $(CXXFLAGS) -lpthread $^ -o $@

clean:
	-rm -f *.o $(TESTS) replica client .pipes/*

.PHONY: depend
depend: .depend

.depend: $(SRCS)
	-rm -f .depend
	-$(CXX) $(CXXFLAGS) -MM $^ > .depend

include .depend

