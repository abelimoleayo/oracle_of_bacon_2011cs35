/* Author: Imoleayo Abel
 * CS35 Lab 11
 * December 5, 2011
 */

#include <limits.h>
#include "binaryheap.h"

using std::vector;

template <typename V, typename E, typename W>
vector<V> dfs(V src, V dest, Graph<V,E,W>* g) {
  if (!g->containsVertex(src) || !g->containsVertex(dest)) {
    throw std::runtime_error("dfs called on vertex not in specified graph");   
  } // ensure src and dest are in graph
  vector<V> outVect, searchVect;
  HashTable<V,V>* isVisitedFrom = new HashTable<V,V>;
  searchVect.push_back(src);
  V current;
  while (!searchVect.empty()) {
    current = searchVect[searchVect.size()-1];
    searchVect.pop_back();
    if (current == dest) {  // if destination is reached
      break;
    }
    vector<V> neighbors = g->getNeighbors(current); // adjacent neighbors
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      if (!isVisitedFrom->containsKey(neighbor)) { // if not yet visited
        isVisitedFrom->put(neighbor,current);
        searchVect.push_back(neighbor);
      }
    }
  }
  if (current == dest) {    // if a path was found
    outVect.push_back(current);  // add source to output vector
    while (current != src) {
      outVect.push_back(isVisitedFrom->get(current));
      current = isVisitedFrom->get(current);
    } // at this point vector is ordered backwards
    for (int i = 0; i < outVect.size()/2; i++) { // order vector
      V temp = outVect[i];
      outVect[i] = outVect[outVect.size() - 1 - i];
      outVect[outVect.size() - 1 - i] = temp;
    }
  }
  delete isVisitedFrom;
  return outVect;
}


template <typename V, typename E, typename W>
vector<V> bfs(V src, V dest, Graph<V,E,W>* g) {
  if (!g->containsVertex(src) || !g->containsVertex(dest)) {
    throw std::runtime_error("bfs called on vertex not in graph");
  } // ensure graph contains source and destination
  vector<V> outVect;
  ArrayQueue<V>* searchQueue = new ArrayQueue<V>;
  HashTable<V,V>* isVisitedFrom = new HashTable<V,V>;
  searchQueue->enqueue(src);
  V current;
  while (!searchQueue->isEmpty()) {
    current = searchQueue->dequeue();
    if (current == dest) {
      break;  // if destination is reached
    }
    vector<V> neighbors = g->getNeighbors(current);  // current's neighbors
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      if (!isVisitedFrom->containsKey(neighbor)) { // if neigh is  visited
        isVisitedFrom->put(neighbor,current);
        searchQueue->enqueue(neighbor);
      }
    }
  }
  if (current == dest) {  // if path found
    outVect.push_back(current);
    while (current != src) {
      outVect.push_back(isVisitedFrom->get(current));
      current = isVisitedFrom->get(current);
    }  // here, the output vector is sorted in reversed other
    for (int i = 0; i < outVect.size()/2; i++) {  // order vector enteries
      V temp = outVect[i];
      outVect[i] = outVect[outVect.size() - 1 - i];
      outVect[outVect.size() - 1 - i] = temp;
    }
  }
  delete searchQueue;
  delete isVisitedFrom;
  return outVect;
}


template <typename V, typename E, typename W>
vector<V> weightedBfs(V src, V dest, Graph<V,E,W>* g) {
  if (!g->containsVertex(src) || !g->containsVertex(dest)) {
    throw std::runtime_error("weigtedBfs called on vertex not in graph");
  } // confirm src and dest are in graph
  vector<V> outVect, allVertices;
  allVertices = g->getVertices();
  HashTable<V,Pair<int,V> >* distanceTable = new HashTable<V,Pair<int,V> >;
  BinaryHeap<W,V>* PQ = new BinaryHeap<W,V>;
  for (int i = 0; i < allVertices.size(); i++) { // set all distances to
    distanceTable->put(allVertices[i],Pair<int,V>(INT_MAX,dest)); // infinity
  }
  distanceTable->put(src,Pair<int,V>(0,dest)); // set src distance to zero
  PQ->insert(0,src);  // add src to priority queue
  V current;
  while (!PQ->isEmpty()) {
    current = PQ->removeMin();
    if (current == dest) {   // if destination is reached
      break;
    }
    int currentDist = distanceTable->get(current).first;
    vector<V> neighbors = g->getNeighbors(current);
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      int neighborDist = distanceTable->get(neighbor).first;
      W currNeighEdgeCost = g->getEdge(current,neighbor).getWeight();
      if (currentDist + currNeighEdgeCost < neighborDist) {
        distanceTable->put(neighbor,Pair<int,V>(currentDist + currNeighEdgeCost
              ,current));
        PQ->insert(currentDist + currNeighEdgeCost, neighbor);
      }
    }
  }
  if (current == dest) {  // if a path is found
    outVect.push_back(current);
    while(current != src) {
      outVect.push_back(distanceTable->get(current).second);
      current = distanceTable->get(current).second;
    } // here, path is in reversed order
    for (int i = 0; i < outVect.size()/2; i++) {  // re-order path
      V temp = outVect[i];
      outVect[i] = outVect[outVect.size() - 1 - i];
      outVect[outVect.size() - 1 - i] = temp;
    }
  } 
  delete distanceTable;
  delete PQ;
  return outVect;
}


template <typename V, typename E, typename W>
int getUnweightedPathLength(V src, V dest, Graph<V,E,W>* g) {
  if (!g->containsVertex(src) || !g->containsVertex(dest)) {
    throw std::runtime_error("getUnweightedPathLength called on vertex not in \
        graph");
  } // ensure graph conatins src and dest 
  if (src == dest) {
    return 0;
  }
  int numVertices = bfs(src, dest, g).size(); // get shortest path using bfs
  if (numVertices < 2) {
    throw std::runtime_error("numEdgesBetween called on pair in different \
        component");
  }
  return numVertices-1;
}

template <typename V, typename E, typename W>
int getWeightedPathLength(V src, V dest, Graph<V,E,W>* g) {
  if (!g->containsVertex(src) || !g->containsVertex(dest)) {
    throw std::runtime_error("getWeightedPathLength called on vertex not in \
        graph");
  } // ensure graph contains src and dest
  if (src == dest) {
    return 0;
  }
  HashTable<V,int>* distanceTable = new HashTable<V,int>;
  BinaryHeap<W,V>* PQ = new BinaryHeap<W,V>;
  vector<V> allVertices = g->getVertices();
  for (int i = 0; i < allVertices.size(); i++) {
    distanceTable->put(allVertices[i],INT_MAX);  // set all dists to infinity
  }
  distanceTable->put(src,0); // set src's dist to 0
  PQ->insert(0,src);         // add src to priority queue
  while (!PQ->isEmpty()) {
    V current = PQ->removeMin();
    if (current == dest) {   // destination found
      break;
    }
    int currentDist = distanceTable->get(current);
    vector<V> neighbors = g->getNeighbors(current);
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      int neighborDist = distanceTable->get(neighbor);
      W currNeighEdgeCost = g->getEdge(current,neighbor).getWeight();
      if (currentDist + currNeighEdgeCost < neighborDist) {
        distanceTable->put(neighbor, currentDist + currNeighEdgeCost);
        PQ->insert(currentDist + currNeighEdgeCost, neighbor);
      }
    }
  }
  W distance = distanceTable->get(dest);
  delete distanceTable;
  delete PQ;
  if (distance == INT_MAX) {  // if src & dest are not connected
    throw std::runtime_error("getWeightedPathLength called on vertices in \
        different component");
  }
  return distance;
}


template <typename V, typename E, typename W>
double averageDistance(V src, Graph<V,E,W>* g) {
  if (!g->containsVertex(src)) {
    throw std::runtime_error("averageDistance called on vertex not in graph");
  }  // ensure src is drake
  HashTable<V,int>* distanceTable = new HashTable<V,int>;
  ArrayQueue<V>* searchQueue = new ArrayQueue<V>;
  vector<V> allVertices = g->getVertices();
  if (allVertices.size() == 1) {  // if graph has just one vertex
    return 0;
  }
  double totalDistance = 0.0;
  double totalVertices = 0.0;
  for (int i = 0; i < allVertices.size(); i++) { // set all dists to infinity
    distanceTable->put(allVertices[i],INT_MAX);
  }
  distanceTable->put(src,0);  // set src distance to 0
  searchQueue->enqueue(src);
  while (!searchQueue->isEmpty()) {
    V current = searchQueue->dequeue();
    int currentDist = distanceTable->get(current);
    totalDistance += currentDist;
    totalVertices += 1;
    vector<V> neighbors = g->getNeighbors(current);
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      if (distanceTable->get(neighbor) == INT_MAX) {
        distanceTable->put(neighbor,currentDist + 1);
        searchQueue->enqueue(neighbor);
      }
    }
  }
  double averageDist = totalDistance/(totalVertices - 1);
  delete distanceTable;
  delete searchQueue;
  return averageDist;
}


template <typename V, typename E, typename W>
double averageWeightedDistance(V src, Graph<V,E,W>* g) {
  if (!g->containsVertex(src)) {
    throw std::runtime_error("averageWeightedDistance called on vertex not in \
        graph");
  } // ensure graph contains src
  HashTable<V,int>* distanceTable = new HashTable<V,int>;
  BinaryHeap<W,V>* PQ = new BinaryHeap<W,V>;
  vector<V> allVertices = g->getVertices();
  if (allVertices.size() == 1) {  // if graph has only one vertex
    return 0;
  }
  double totalDistance = 0.0;
  double totalVertices = 0.0;
  for (int i = 0; i < allVertices.size(); i++) { // set all dists to infinity
    distanceTable->put(allVertices[i],INT_MAX);
  }
  distanceTable->put(src,0);  // set src distance to 0
  PQ->insert(0,src);
  while (!PQ->isEmpty()) {
    V current = PQ->removeMin();
    int currentDist = distanceTable->get(current);
    totalDistance += currentDist;
    totalVertices += 1;
    vector<V> neighbors = g->getNeighbors(current);
    for (int i = 0; i < neighbors.size(); i++) {
      V neighbor = neighbors[i];
      int neighborDist = distanceTable->get(neighbor);
      W currNeighEdgeCost = g->getEdge(current,neighbor).getWeight();
      if (currentDist + currNeighEdgeCost < neighborDist) {
        distanceTable->put(neighbor, currentDist + currNeighEdgeCost);
        PQ->insert(currentDist + currNeighEdgeCost, neighbor);
      }
    }
  }
  double averageDist = totalDistance/(totalVertices - 1);
  delete distanceTable;
  delete PQ;
  return averageDist;
}
