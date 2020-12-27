CXX = g++
CXXFLAGS = -O3

# Add any new .h and .inl files to the INCLUDES definition below:
INCLUDES = pair.h \
	   iterator.h queuebasediterator.h queuebasediterator.inl \
	   queue.h arrayqueue.h arrayqueue.inl \
	   list.h circulararraylist.h circulararraylist.inl \
	   dictionary.h hashtable.h hashtable.inl \
           edge.h edge.inl graph.h graph.inl \
           graph-algorithms.h graph-algorithms.inl \
	   binaryheap.h binaryheap.inl


# If you create any new non-templated classes, add an appropriate .o file
# to the OBJECTS definition below:
OBJECTS = 


# If you create a new test program, add the name of the test program
# to the PROGRAMS definition below and then create a rule for that program
PROGRAMS = testGraph oracle

all: $(PROGRAMS)

testGraph: $(INCLUDES) $(OBJECTS) testGraph.cc
	$(CXX) $(CXXFLAGS) -o $@ $@.cc $(OBJECTS)

oracle: $(INCLUDES) $(OBJECTS) oracle.cc
	$(CXX) $(CXXFLAGS) -o $@ $@.cc $(OBJECTS)

%.o: %.cc %.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(PROGRAMS)

.PHONY: all clean
