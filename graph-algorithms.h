#include <vector>
using std::vector;
#include "graph.h"


/**
 * Returns the path found from the vertex src to the vertex dest,
 * using an unweighted depth-first search of the graph.
 */
template <typename V, typename E, typename W>
vector<V> dfs(V src, V dest, Graph<V,E,W>* g);


/**
 * Returns the path found from the vertex src to the vertex dest,
 * using an unweighted breadth-first search of the graph.
 */
template <typename V, typename E, typename W>
vector<V> bfs(V src, V dest, Graph<V,E,W>* g);


/**
 * Returns the path found from the vertex src to the vertex dest,
 * using a weighted breadth-first search of the graph.
 */
template <typename V, typename E, typename W>
vector<V> weightedBfs(V src, V dest, Graph<V,E,W>* g);


/**
 * Returns the number of edges in the shortest path from src to dest.
 */
template <typename V, typename E, typename W>
int getUnweightedPathLength(V src, V dest, Graph<V,E,W>* g);


/**
 * Returns the cost of the shortest path from src to dest.
 */
template <typename V, typename E, typename W>
int getWeightedPathLength(V src, V dest, Graph<V,E,W>* g);


/**
 * Given a vertex src, returns the average distance (no. of edges) between src
 * and all other vertices reachable from src.
 */
template <typename V, typename E, typename W>
double averageDistance(V src, Graph<V,E,W>* g);

/**
 * Given a vertex src, returns the average distance (cost W) between src and
 * all other vertices reacheable from src.
 */
template <typename V, typename E, typename W>
double averageWeightedDistance(V src, Graph<V,E,W>* g);

#include "graph-algorithms.inl"

