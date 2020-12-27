/* Author: Imoleayo Abel
 * CS35 Lab 11
 * December 5, 2011
 */

#include <stdexcept>

/**
 * Constructs an empty graph, containing no edges or vertices.
 */
template <typename V, typename E, typename W>
Graph<V,E,W>::Graph() {
}


/**
 * Destructs a graph.
 */
template <typename V, typename E, typename W>
Graph<V,E,W>::~Graph() {
  Iterator<Pair<V,V*> >* vIt = vertexCache.getIterator();
  while (vIt->hasNext()) {
    delete vIt->getNext().second;
  }
  delete vIt;

  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it = outgoingEdges.getIterator();
  while (it->hasNext()) {
    delete it->getNext().second;
  }
  delete it;
}


/**
 * Inserts a vertex into the graph, throwing an exception if the given vertex
 * was already in the graph.
 */
template <typename V, typename E, typename W>
void Graph<V,E,W>::insertVertex(V v) {
  if (outgoingEdges.containsKey(v)) {
    throw std::runtime_error("Tried to enter a duplicate vertex.");
  }
  V* p = new V(v);
  vertexCache.put(v,p);
  outgoingEdges.put(v, new vector<Edge<V,E,W> >());
}


/**
 * Removes a vertex and all its associated edges (outgoing and incoming)
 * from the graph.  Throws an exception if the given vertex is not in
 * the graph.
 */
template <typename V, typename E, typename W>
void Graph<V,E,W>::removeVertex(V v) {
  V* p = vertexCache.get(v);

  delete outgoingEdges.get(v);
  outgoingEdges.remove(v);

  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it =
      outgoingEdges.getIterator();
  while (it->hasNext()) {
    vector<Edge<V,E,W> >* edgeList = it->getNext().second;
    for (int i = edgeList->size()-1; i >= 0; --i) {
      if ((*edgeList)[i].dest == p) {
        edgeList->erase(edgeList->begin()+i);
      }
    }
  }
  delete it;
  delete p;
  vertexCache.remove(v);
}


/**
 * Given a source vertex src, a destination vertex dest, and edge label
 * and an (optional) weight, inserts an edge into the graph.  Also inserts
 * the given src and dest vertices if they are not already in the graph.
 * Replaces the given src->dest edge if the edge is already in the graph.
 */
template <typename V, typename E, typename W>
void Graph<V,E,W>::insertEdge(V src, V dest, E label, W weight) {
  if (!outgoingEdges.containsKey(src)) {
    insertVertex(src);
  }
  if (!outgoingEdges.containsKey(dest)) {
    insertVertex(dest);
  }

  V* srcP = vertexCache.get(src);
  V* destP = vertexCache.get(dest);

  vector<Edge<V,E,W> >* edgeList = outgoingEdges.get(src);
  Edge<V,E,W> newEdge(srcP, destP, label, weight);

  for (int i = 0; i < edgeList->size(); ++i) {
    if ((*edgeList)[i].src == srcP && (*edgeList)[i].dest == destP) {
      (*edgeList)[i] = newEdge;
      return;
    }
  }

  edgeList->push_back(newEdge);
}


/**
 * Given a source vertex src and destination vertex dest, removes the src->dest
 * edge from the graph.  Throws an exception if src->dest is not in the graph.
 */
template <typename V, typename E, typename W>
void Graph<V,E,W>::removeEdge(V src, V dest) {
  if (!outgoingEdges.containsKey(src)) {
    throw std::runtime_error("removeEdge called on edge not in graph");
  }

  V* srcP = vertexCache.get(src);
  V* destP = vertexCache.get(dest);
  vector<Edge<V,E,W> >* edgeList = outgoingEdges.get(src);
  for (int i = 0; i < edgeList->size(); ++i) {
    if ((*edgeList)[i].src == srcP && (*edgeList)[i].dest == destP) {
      edgeList->erase(edgeList->begin()+i);
      return;
    }
  }

  throw std::runtime_error("removeEdge called on edge not in graph");
}


/**
 * Returns true if the graph contains the given vertex.
 */
template <typename V, typename E, typename W>
bool Graph<V,E,W>::containsVertex(V v) {
  return outgoingEdges.containsKey(v);
}

/**
 * Returns true if the graph contains the given src->dest edge.
 */
template <typename V, typename E, typename W>
bool Graph<V,E,W>::containsEdge(V src, V dest) {
  if (!containsVertex(src) || !containsVertex(dest)) {
    return false;
  }
  V* destP = vertexCache.get(dest);
  vector<Edge<V,E,W> >* edgeList = outgoingEdges.get(src);
  for (int i = 0; i < edgeList->size(); ++i) {
    if ((*edgeList)[i].dest == destP) {
      return true;
    }
  }
  return false;
}

/**
 * Returns a vector of all edges in the graph.
 */
template <typename V, typename E, typename W>
vector<Edge<V,E,W> > Graph<V,E,W>::getEdges() {
  vector<Edge<V,E,W> > rv;
  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it = 
      outgoingEdges.getIterator();
  while (it->hasNext()) {
    vector<Edge<V,E,W> >* edgeList = it->getNext().second;
    for (int i = 0; i < edgeList->size(); ++i) {
      rv.push_back((*edgeList)[i]);
    }
  }
  delete it;
  return rv;
}


/**
 * Returns a vector of all vertices in the graph.
 */
template <typename V, typename E, typename W>
vector<V> Graph<V,E,W>::getVertices() {
  vector<V> rv;
  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it = 
      outgoingEdges.getIterator();
  while (it->hasNext()) {
    rv.push_back(it->getNext().first);
  }
  delete it;
  return rv;
}


/**
 * Given a vertex src, returns a vector of all outgoing edges for src.
 */
template <typename V, typename E, typename W>
vector<Edge<V,E,W> > Graph<V,E,W>::getOutgoingEdges(V src) {
  return *(outgoingEdges.get(src));
}

/**
 * Given a vertex src, returns a vector of all vertices adjacent to
 * src by an outgoing edge from src.
 */
template <typename V, typename E, typename W>
vector<V> Graph<V,E,W>::getNeighbors(V src) {
  vector<V> neighbors;
  vector<Edge<V,E,W> >* outEdges = outgoingEdges.get(src);
  for (int i = 0; i < outEdges->size(); ++i) {
    neighbors.push_back((*outEdges)[i].getDest());
  }
  return neighbors;
}

/**
 * Given a vertex dest, returns a vector of all vertices adjacent to
 * dest by an incoming edge to dest.
 */
template <typename V, typename E, typename W>
vector<Edge<V,E,W> > Graph<V,E,W>::getIncomingEdges(V dest) {
  vector<Edge<V,E,W> > rv;
  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it =
      outgoingEdges.getIterator();
  while (it->hasNext()) {
    vector<Edge<V,E,W> >* edgeList = it->getNext().second;
    for (int i = 0; i < edgeList->size(); ++i) {
      if ((*edgeList)[i].getDest() == dest) {
        rv.push_back((*edgeList)[i]);
      }
    }
  }
  delete it;
  return rv;
}


/**
 * Given a source vertex src and a destination vertex dest, returns the
 * src->dest edge from the graph.  Throws an exception if src->dest is not
 * in the graph.
 */
template <typename V, typename E, typename W>
Edge<V,E,W> Graph<V,E,W>::getEdge(V src, V dest) {
  vector<Edge<V,E,W> >* edgeList = outgoingEdges.get(src);
  for (int i = 0; i < edgeList->size(); ++i) {
    if ((*edgeList)[i].getDest() == dest) {
      return (*edgeList)[i];
    }
  }
  
  throw std::runtime_error("getEdge called on edge not in graph");
}
    

template <typename V, typename E, typename W>
ostream& operator<<(ostream& out, Graph<V,E,W>& g) {
  Iterator<Pair<V,vector<Edge<V,E,W> >* > >* it =
      g.outgoingEdges.getIterator();
  while (it->hasNext()) {
    Pair<V,vector<Edge<V,E,W> >* > next = it->getNext();
    out << next.first << ": {";
    if (next.second->size() > 0) {
      out << (*(next.second))[0].getDest();
    }
    for (int i = 1; i < next.second->size(); ++i) {
      out << ", " << (*(next.second))[i].getDest();
    }
    out << "}\n";
  }
  delete it;
  return out;
}

