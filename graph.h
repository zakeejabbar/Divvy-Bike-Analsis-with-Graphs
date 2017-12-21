#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/*graph.h*/

#pragma once

#include <iostream>

#include "graph.h"
#include <set>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Graph
{
private:
  class Edge
  {
  public:
    int   Src, Dest, Weight;
    Edge *Next;
  };

  Edge  **Vertices;
  string *Names;
  int     NumVertices;
  int     NumEdges;
  int     Capacity;
  
   vector<int> iGetNeighbors(int v);

public:
  Graph(int N);
  ~Graph();

  bool AddVertex(string v);
  bool AddEdge(string src, string dest, int weight);
  int  FindVertexByName(string name);
  set<string> GetVertices();
  set<string> GetNeighbors(string v);
  bool doesEdgeExist(string fromID, string toID);
  void incrementWeight(string fromID, string toID);
  vector<int> GetEdgeWeights(string src, string dest);
  vector<string> BFS(string v);
  int GetNumVertices();
  int GetNumEdges();

  void PrintGraph(string title);
};


#endif // GRAPH_H_INCLUDED
