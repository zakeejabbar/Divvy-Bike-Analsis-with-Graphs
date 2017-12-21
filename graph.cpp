/*graph.cpp*/

#include <iostream>

#include "graph.h"
#include <set>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


//
// Constructor:
//
Graph::Graph(int N)
{
  this->NumVertices = 0;
  this->NumEdges = 0;
  this->Capacity = N;

  this->Vertices = new Edge*[N];
  this->Names = new string[N];

}


//
// Destructor:
//
Graph::~Graph()
{
  //
  // Future work:
  //
}


//
// AddVertex:
//
// Adds the given vertex v to the graph, returning true if
// successful and false if not.  The add fails if (1) the
// graph is full, or (2) the vertex already exists in the
// graph.
//
bool Graph::AddVertex(string v)
{
   //
   // if the graph is "full", i.e. cannot hold more vertices,
   // then return false:
   //

   if(this->NumVertices == this->Capacity)
   {
      return false;
   }

   int i = this->NumVertices;

   this->Vertices[i] = nullptr;  // head of LL: null
   this->Names[i] = v;           // copy vertex string:

   this->NumVertices++;
   return true;
}

//returns the number of vertices
int Graph::GetNumVertices()
{
    return NumVertices;
}

//returns the number of edges
int Graph::GetNumEdges()
{
    return NumEdges;
}

//
// FindVertexByName:
//
// Helper function to find a vertex by name by
// searching the Names array using linear search.
// Returns vertex # (i.e. array index) or -1 if
// not found:
//
int Graph::FindVertexByName(string name)
{
  int k;
   int S = -1;
   for(k = 0; k < this->Capacity; k++)
   {
      if(this->Names[k] == name)
      {
         S = k;
      }
   }

  return S;
}

// Checks if the edge already exists in the graph
// If it exists returns true, otherwise returns false
bool Graph::doesEdgeExist(string fromID, string toID)
{
	
	int S = this->FindVertexByName(fromID);
	int D = this->FindVertexByName(toID);
	
	if(S == -1 || D == -1)
	{
		return false;
	}
	
   Edge *cur = this->Vertices[S];

   while (cur != nullptr)
   {
      if(D == cur->Dest)
      {
         return true;
      }
      cur = cur->Next;
   }
   
   return false;
}

// Increments the weight of an edge
void Graph::incrementWeight(string fromID, string toID)
{
	int S = this->FindVertexByName(fromID);
	int D = this->FindVertexByName(toID);
	
	Edge *cur = this->Vertices[S];
	while (cur != nullptr)
   {
      if(D == cur->Dest)
      {
         cur->Weight++;
      }

      cur = cur->Next;
   }
}

//
// AddEdge:
//
// Adds an edge from src to dest, with the given weight, returning
// true if successful and false if not.  The add fails if the src
// or dest vertex do not exist.
//
bool Graph::AddEdge(string src, string dest, int weight)
{
	
   int S = this->FindVertexByName(src);
   if(S == -1)
   {
      return false;
   }
   
   //
   // Second, lookup dest vertex in Names array and obtain index D, if
   // not found, return false:
   //
   int D = this->FindVertexByName(dest);
   if(D == -1)
   {
      return false;
   }
      //
   // Now add an edge (S,D,weight) to the front of S's linked-list.
   // You'll need to allocate a new edge using new, store S, D and
   // weight, and then insert at head of S's linked-list in the
   // Vertices array:
   //
   Edge *e = new Edge();
   e->Src = S;
   e->Dest = D;
   e->Weight = weight;

   Edge *prev = nullptr;
   Edge *cur = this->Vertices[S];

   while (cur != nullptr)
   {
      if(D < cur->Dest)
      {
         break;
      }
      prev = cur;
      cur = cur->Next;
   }
   e->Next = cur;
   if(prev == nullptr)
   {
      this->Vertices[S] = e;
   }
   else
   {
      prev->Next = e;
   }

   // ...

   //
   // increment the # of edges and return true:
   //
   this->NumEdges++;
   return true;

   return false;
}


//
// GetVertices:
//
// Returns a set containing all vertices in the graph.
//
set<string> Graph::GetVertices()
{
   set<string>  vertices;

   for(int i = 0; i < this->NumVertices; i++)
   {
      vertices.insert(this->Names[i]);
   }

   return vertices;
}


//
// GetNeighbors:
//
// Returns a set containing all the vertices adjacent to v.
// If v does not exist in the graph, the returned set is
// empty.
//
set<string> Graph::GetNeighbors(string v)
{
  set<string>  neighbors;
  
  int S = this->FindVertexByName(v); 

  Edge *temp = this->Vertices[S];

  while(temp != nullptr)
  {
     neighbors.insert(this->Names[temp->Dest]);
     temp = temp->Next;
  }

  return neighbors;
}

// Gets all the neighbors of a vertex
// and stores then in an int vector
vector<int> Graph::iGetNeighbors(int v)
{
  vector<int>  neighbors;

  int S = v;
  if(S == -1)
  {
     return neighbors;
  }

  Edge *temp = this->Vertices[S];

  while(temp != nullptr)
  {
     neighbors.push_back(temp->Dest);
     temp = temp->Next;
  }

  return neighbors;
}

//
// BFS:
//
// Performs a breadth-first search starting from vertex v, returning
// a vector that denotes the order in vertices were visited.  If v
// does not exist in the graph, an empty vector is returned.
//
// NOTE that a vertex will appear at most once in the returned vector,
// since once a vertex is visited, it is never visited again.
//
vector<string> Graph::BFS(string v)
{
  vector<string>  visited;
  queue<int>      frontierQueue;
  set<int>        discoveredSet;

  int start = this->FindVertexByName(v);
  if(start < 0)
  {
     return visited;
  }

  frontierQueue.push(start);
  discoveredSet.insert(start);

  while(frontierQueue.empty() != true)
  {
     int currentV = frontierQueue.front();
     frontierQueue.pop();
     visited.push_back(this->Names[currentV]);
     vector<int> V = iGetNeighbors(currentV);
     for(int adjV: V)
     {
        if ( discoveredSet.find(adjV) == discoveredSet.end() )  // not found:
        {
           frontierQueue.push(adjV);
           discoveredSet.insert(adjV);
        }
        else // set contains e:
        {
           continue;
        }
     }
  }





  return visited;
}


//
// GetEdgeWeights:
//
// Returns a vector containing all the weights for edges
// from src to dest.  The weights are in ascending order,
// and may contain duplicates (since it is legal for there
// to be 2 different edges from src to dest with the same
// weight).  If src or dest do not exist in the graph, the
// returned vector is empty.
//
vector<int> Graph::GetEdgeWeights(string src, string dest)
{
   vector<int> weights;

   int S = this->FindVertexByName(src);
   int D = this->FindVertexByName(dest);

   if(S == -1 || D == -1)
   {
      return weights;
   }

  Edge *temp = this->Vertices[S];

  while(temp != nullptr)
  {
     if(temp->Dest == D)
     {
        weights.push_back(temp->Weight);
     }
     temp = temp->Next;
  }



   return weights;
}


//
// PrintGraph:
//
// Prints the graph, typically for debugging purposes.
//
void Graph::PrintGraph(string title)
{
  cout << ">>Graph: " << title << endl;
  cout << "  # of vertices: " << this->NumVertices << endl;
  cout << "  # of edges:    " << this->NumEdges << endl;
  cout << "  Capacity:      " << this->Capacity << endl;

  cout << "  Vertices:" << endl;

  for (int v = 0; v < this->NumVertices; ++v)
  {
    cout << "    " << v << " (" << this->Names[v] << "): ";

    Edge *edge = this->Vertices[v];
    while (edge != nullptr)
    {
      cout << "(" << edge->Src << "," << edge->Dest << "," << edge->Weight << ")";

      edge = edge->Next;
      if (edge != nullptr)
        cout << ", ";
    }

    cout << endl;
  }
}
