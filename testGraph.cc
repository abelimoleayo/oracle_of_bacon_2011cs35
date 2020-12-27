/* Imoleayo Abel
 * CS35 Lab 11
 * December 5, 2011
 */
#include <assert.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "graph.h"
#include "graph-algorithms.h"

using namespace std;

int main() {
  Graph<string,int,int>* myGraph = new Graph<string,int,int>;
  string sea, sfo, lax, phx, ord, stl, hou, pit, clt, phl, jfk, bos;
  sea = "SEA"; sfo = "SFO"; lax = "LAX"; phx = "PHX"; ord = "ORD"; stl = "STL";
  hou = "HOU"; pit = "PIT"; clt = "CLT"; phl = "PHL"; jfk = "JFK"; bos = "BOS";

  /* weighted graph example from class */
  myGraph->insertEdge(sea,sfo,1,3);
  myGraph->insertEdge(sfo,sea,31,3);
  myGraph->insertEdge(sfo,lax,2,10);
  myGraph->insertEdge(lax,sfo,32,10);
  myGraph->insertEdge(lax,phx,3,9);
  myGraph->insertEdge(phx,lax,33,9);
  myGraph->insertEdge(lax,jfk,4,29);
  myGraph->insertEdge(jfk,lax,34,29);
  myGraph->insertEdge(sfo,phx,5,3);
  myGraph->insertEdge(phx,sfo,35,3);
  myGraph->insertEdge(sfo,ord,6,10);
  myGraph->insertEdge(ord,sfo,36,10);
  myGraph->insertEdge(sea,ord,7,3);
  myGraph->insertEdge(ord,sea,37,3);
  myGraph->insertEdge(phx,ord,8,7);
  myGraph->insertEdge(ord,phx,38,7);
  myGraph->insertEdge(lax,hou,9,3);
  myGraph->insertEdge(hou,lax,39,3);
  myGraph->insertEdge(phx,hou,10,3);
  myGraph->insertEdge(hou,phx,40,3);
  myGraph->insertEdge(phx,stl,11,9);
  myGraph->insertEdge(stl,phx,41,9);
  myGraph->insertEdge(sea,bos,12,12);
  myGraph->insertEdge(bos,sea,42,12);
  myGraph->insertEdge(ord,jfk,13,12);
  myGraph->insertEdge(jfk,ord,43,12);
  myGraph->insertEdge(jfk,bos,14,2);
  myGraph->insertEdge(bos,jfk,44,2);
  myGraph->insertEdge(ord,pit,15,4);
  myGraph->insertEdge(pit,ord,45,4);
  myGraph->insertEdge(pit,stl,16,4);
  myGraph->insertEdge(stl,pit,46,4);
  myGraph->insertEdge(pit,jfk,17,10);
  myGraph->insertEdge(jfk,pit,47,10);
  myGraph->insertEdge(jfk,phl,18,3);
  myGraph->insertEdge(phl,jfk,48,3);
  myGraph->insertEdge(pit,phl,19,4);
  myGraph->insertEdge(phl,pit,49,4);
  myGraph->insertEdge(clt,phl,20,8);
  myGraph->insertEdge(phl,clt,50,8);
  myGraph->insertEdge(hou,clt,21,11);
  myGraph->insertEdge(clt,hou,51,11);
  myGraph->insertEdge(stl,clt,22,4);
  myGraph->insertEdge(clt,stl,52,4);

  /* test all graph-algorithms */
  vector<string> myBfs = bfs(phl,lax,myGraph);
  vector<string> myWeightedBfs = weightedBfs(phl,lax,myGraph);
  vector<string> myDfs = dfs(phl,lax,myGraph);
  int unweightedPathLength = getUnweightedPathLength(phl,lax,myGraph);
  int weightedPathLength = getWeightedPathLength(phl,lax,myGraph);
  double avgUnweightedDist = averageDistance(phl,myGraph);
  double avgWeightedDist = averageWeightedDistance(phl,myGraph);
  cout << "Breadth First: " << endl;
  for (int i = 0; i < myBfs.size(); i++) {
    cout << "\t" << myBfs[i] << endl;
  }
  cout << "Weighted Breadth First: " << endl;
  for (int i = 0; i < myWeightedBfs.size(); i++) {
    cout << "\t" << myWeightedBfs[i] << endl;
  }
  cout << "Depth First: " << endl;
  for (int i = 0; i < myDfs.size(); i++) {
    cout << "\t" << myDfs[i] << endl;
  }
  cout << "unWeighted PathLength: " << unweightedPathLength << endl;
  cout << "Weighted PathLength: " << weightedPathLength << endl;
  cout << "Avg Unweighted Dist: " << avgUnweightedDist << endl;
  cout << "Avg Weighted Dist: " << avgWeightedDist << endl;
  cout << *myGraph << endl;
  delete myGraph;
  return 0;
}
