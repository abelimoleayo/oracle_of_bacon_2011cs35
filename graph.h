#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>   // A vector is the C++ Standard Template Library 
using std::vector;  // implementation of an ArrayList.  It's official
                    // documentation is at:
                    // http://new.cplusplus.com/reference/stl/vector/
                   
#include <iostream>
using std::ostream;

                    // Forward declaration of the Graph, so that the Edge
                    // class can friend us.
template <typename V, typename E, typename W> class Graph;

#include "edge.h"
#include "hashtable.h"

                    // For printing a graph using a C++ ostream.
template <typename V, typename E, typename W>
ostream& operator<<(ostream& out, Graph<V,E,W>& g);

/**
 * A Graph is a class that represents a directed, weighted graph.
 * It is templated on three types:
 *   V:  a type to represent the vertex labels, and 
 *   E:  a type to represent the edge labels, and 
 *   W:  a type to represent the weight (usually an int, float, or double).
 *
 * This implementation represents the graph using edge adjacency lists:
 * for each vertex v, the graph stores the list of v's outgoing edges.
 * All vertex-edgelist pairs are stored in a HashTable with the vertex as the
 * key and a pointer to the edge list as the value.
 */
template <typename V, typename E, typename W>
class Graph {
  private:
                                         // This graph is stored using an edge-
                                         // list representation:  for each 
                                         // vertex v, we store the list of v's 
                                         // outgoing edges. outgoingEdges is a 
                                         // dictionary of all the 
                                         // vertex-edgelist pairs.
    HashTable<V,vector<Edge<V,E,W> >* > outgoingEdges;
 
                                         // Caches vertex labels, so that we
                                         // can efficiently compare label
                                         // pointers instead of the labels
    HashTable<V,V*> vertexCache;         // themselves.

  public:
    Graph();                             // Constructs a graph, initially with
                                         // no vertices or edges.
    ~Graph();                            // Destructs the graph.

    void insertVertex(V v);              // Inserts vertex v into the graph.
    void removeVertex(V v);              // Removes vertex v from the graph,
                                         // or throws an exception if v is not
                                         // in the graph.
                                         
                                         // Inserts a new directed edge from
                                         // src->dest into the graph, with 
                                         // default edge weight 1.  insertEdge
                                         // will insert the vertices src and
                                         // dest if they are not already in
                                         // the graph, and will replace the
                                         // src->dest edge with the new label
                                         // and weight if src->dest was already
                                         // in the graph.
    void insertEdge(V src, V dest, E label, W weight = 1);
    void removeEdge(V src, V dest);      // Removes the directed edge src->dest
                                         // or throws an exception if src->dest
                                         // is not in the graph.
    bool containsVertex(V v);            // Returns if graph contains vertex v.
    bool containsEdge(V src, V dest);    // Returns true if the graph contains
                                         // the directed edge src->dest.
    Edge<V,E,W> getEdge(V src, V dest);  // Returns the directed edge src->dest
                                         // or throws an exception if src->dest
                                         // is not in the graph.

    vector<Edge<V,E,W> > getEdges();     // Returns list of all edges in graph.
    vector<V>            getVertices();  // Returns all vertices in graph.
              
                                         // For a given vertex src, returns a 
                                         // list of src's outgoing edges.
    vector<Edge<V,E,W> > getOutgoingEdges(V src);

                                         // For a given vertex src, returns a 
                                         // list of the vertices dest such that
                                         // the graph contains edge src->dest.
    vector<V>            getNeighbors(V src);

                                         // For a given vertex dest, returns a
                                         // list of the vertices src such that
                                         // the graph contains edge src->dest.
    vector<Edge<V,E,W> > getIncomingEdges(V dest); 

    friend ostream& operator<< <V,E,W>(ostream& out, Graph<V,E,W>& g);
};

#include "graph.inl"

#endif
