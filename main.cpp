
/*main.cpp*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>

#include "graph.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS  // ignore C-related security warnings in Visual Studio:


//
// Defines a Divvy Station:
//
class Station
{
public:
  string Name;
  int    ID;
  double Latitude;
  double Longitude;
  int    Capacity;

  Station(string name, int id, double latitude, double longitude, int capacity)
  {
    Name = name;
    ID = id;
    Latitude = latitude;
    Longitude = longitude;
    Capacity = capacity;
  }
};


//
// Inputs the stations from the given file, adding each station name as a
// vertex to the graph, and storing a new Station object into the vector.
// The graph is passed by reference --- note the & --- so that the changes
// made by the function are returned back.  The vector of Station objects is
// returned by the function.
//
vector<Station> InputStations(Graph& G, string filename)
{
  string line;
  vector<Station> V;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return V;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   id,name,latitude,longitude,dpcapacity,online_date
    //   456,2112 W Peterson Ave,41.991178,-87.683593,15,5/12/2015
    //   101,63rd St Beach,41.78101637,-87.57611976,23,4/20/2015
    //
    string  stationID, name, latitude, longitude, capacity;

    //
    // parse the line:
    //
    getline(ss, stationID, ',');
    getline(ss, name, ',');
    getline(ss, latitude, ',');
    getline(ss, longitude, ',');
    getline(ss, capacity, ',');

    //
    // Create a new station object:
    //
    Station S(name,
      stoi(stationID),
      stod(latitude),
      stod(longitude),
      stoi(capacity));
      
    int i = stoi(stationID);      
      
    V.push_back(S);
    G.AddVertex(name);


    //
    // TODO:
    //   1. add station object to vector
    //   2. add vertex to graph
    //



    getline(input, line);
  }

  return V;
}


//
// Inputs the trips, adding / updating the edges in the graph.  The graph is
// passed by reference --- note the & --- so that the changes made by the
// function are returned back.  The vector of stations is needed so that
// station ids can be mapped to names; it is passed by reference only for
// efficiency (so that a copy is not made).
//
void ProcessTrips(string filename, Graph& G, vector<Station>& stations)
{
  string line;

  ifstream input(filename);
  if (!input.good())  // failed to open:
    return;

  getline(input, line);  // skip first line: column headers
  getline(input, line);  // first line of real data

  while (!input.eof())  // for each line of input:
  {
    stringstream  ss(line);

    // format:
    //   trip_id,starttime,stoptime,bikeid,tripduration,from_station_id,from_station_name,to_station_id,to_station_name,usertype,gender,birthyear
    //   10426561,6/30/2016 23:35,7/1/2016 0:02,5229,1620,329,Lake Shore Dr & Diversey Pkwy,307,Southport Ave & Clybourn Ave,Subscriber,Male,1968
    //
    string  tripID, fromID, toID, skip;

    //
    // parse the input line:
    //
    getline(ss, tripID, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, skip, ',');
    getline(ss, fromID, ',');
    getline(ss, skip, ',');
    getline(ss, toID, ',');
    getline(ss, skip, ',');
    
    int from = stoi(fromID);
    int to = stoi(toID);
    
    string src;
       for(Station x : stations)
	   {
	  	 if(x.ID == from)
	  	 {
	  	 	src = x.Name;
	     }
	   }
      
      string dest;
       for(Station x : stations)
	   {
	  	 if(x.ID == to)
	  	 {
	  	 	dest = x.Name;
		 }
	   }
    
    

    //
    // NOTE: don't trust the names in the trips file, not always accurate.  Trust the
    // from and to station ids, and then lookup in our vector of stations:
    //
    
    if(G.doesEdgeExist(src, dest) == true)
    {
    	G.incrementWeight(src, dest);
	}
	else
	{
		G.AddEdge(src, dest, 1);
	}


    //
    // TODO:
    //  - add new edge or update existing edge for this trip
    //



    getline(input, line);
  }
}

// Does the info command
void Info(Graph& G, vector<Station>& stations, int fromID)
{
	  int found = 0;
      string src;
      // Checks if station exists, if it does prints out info
      for(Station x : stations)
	  {
	  	 if(x.ID == fromID)
	  	 {
	  	 	found = 1;
	  	 	src = x.Name;
	  	 	cout << x.Name << endl;
	  	 	cout << "(" << x.Latitude << "," << x.Longitude << ")" << endl;
	  	 	cout << "Capacity: " << x.Capacity << endl;
		 }
	  }
	  
	  // If station exists prints out the rest of the info
	  if(found == 1)
	  {
	  	set<string> neighbors = G.GetNeighbors(src);
	  	int totTrips = 0;
	  	
	  	for (string n : neighbors)
        {
        	vector<int> weights = G.GetEdgeWeights(src, n);
        	totTrips += weights[0];
        }
	  	
	  	cout << "# of destination stations:    " << neighbors.size() << endl;
	  	cout << "# of trips to those stations: " << totTrips << endl;
	  	
	  	cout << "Station: trips" << endl;
	  	
	  	for (string n : neighbors)
        {
        	int dest;
        	for(Station x : stations)
	   		{
	  	 		if(x.Name == n)
	  	 		{
	  	 			dest = x.ID;
	     		}
	   		}
	   		
          vector<int> weights = G.GetEdgeWeights(src, n);
          cout << "   " << n << " (" << dest << "): " << weights[0] << endl;
        }
	  	
	  }
	  
	  // If station doesn't exist...
	  if(found == 0)
	  {
	  	cout << "** No such station..." << endl;
	  }
}

// Does the trips command
void Trips(Graph& G, vector<Station>& stations, int fromID, int toID)
{
	string src;
      // Gets the name of the fromID station
       for(Station x : stations)
	   {
	  	 if(x.ID == fromID)
	  	 {
	  	 	src = x.Name;
	     }
	   }
      
      string dest;
      // Gets the name of the toID station
       for(Station x : stations)
	   {
	  	 if(x.ID == toID)
	  	 {
	  	 	dest = x.Name;
		 }
	   }
      
      // Checks if the strings are empty(station doesn't exist)
      if(src.empty() == true  || dest.empty() == true)
      {
      	cout << "** One of those stations doesn't exist..." << endl;
	  }
	  else
	  {
	  	// prints out the rest of the info if stations exist
	  	cout << src << " -> " << dest << endl;
	  	
	  	// Edge doesn't exist so there are no trips
	  	if(G.doesEdgeExist(src, dest) == false)
	  	{
	  		cout << "# of trips: 0" << endl;
	    }
	    else
	    {
	    	vector<int> weights = G.GetEdgeWeights(src, dest);
	    	cout << "# of trips: " << weights[0] << endl;
		}
	  	
	  	
	  }
}

// Does the bfs command
void Bfs(Graph& G, vector<Station>& stations, int fromID)
{
	string src;
      // Gets the name of the fromID station
       for(Station x : stations)
	   {
	  	 if(x.ID == fromID)
	  	 {
	  	 	src = x.Name;
	     }
	   }
      
      // If station doesn't exist...
      if(src.empty() == true)
      {
      	cout << "** No such station..." << endl;
	  }
	  else
	  {
	  	// If station does exist prints out the info
	  	vector<string> bfs = G.BFS(src);
      
        cout << "# of stations: " << bfs.size() << endl; 
		
		for (string n : bfs)
        {
        	int nums;
        	for(Station x : stations)
	   		{
	  	 		if(x.Name == n)
	  	 		{
	  	 			nums = x.ID;
	  	 			cout << nums << ", ";
	     		}
	   		}
	   	}          	 
	    
	    cout << "#" << endl;
	  }
}


//
// getFileName:
//
// Inputs a filename from the keyboard, checks that the file can be
// opened, and returns the filename if so.  If the file cannot be
// opened, an error message is output and the program is exited.
//
string getFileName()
{
  string filename;

  // input filename from the keyboard:
  getline(cin, filename);

  // make sure filename exists and can be opened:
  ifstream file(filename);
  if (!file.good())
  {
    cout << "**Error: unable to open '" << filename << "'" << endl << endl;
    std::terminate();
  }

  return filename;
}


int main()
{
  int    N = 1000;
  Graph  DivvyGraph(N);

  cout << "** Divvy Graph Analysis **" << endl;

  string stationsFilename = getFileName();
  string tripsFilename = getFileName();

  vector<Station> stations = InputStations(DivvyGraph, stationsFilename);
  ProcessTrips(tripsFilename, DivvyGraph, stations);

  cout << ">> Graph:" << endl;
  cout << "   # of vertices: " << DivvyGraph.GetNumVertices() << endl;
  cout << "   # of edges:    " << DivvyGraph.GetNumEdges() << endl;
  cout << ">> Ready:" << endl;

  string cmd;
  int    fromID, toID;

  cout << ">> ";
  cin >> cmd;

  while (cmd != "exit")
  {
    if (cmd == "info")
    {
      cin >> fromID;
      
      Info(DivvyGraph, stations, fromID);
      
    }
    else if (cmd == "trips")
    {
      cin >> fromID;
      cin >> toID;
      
      Trips(DivvyGraph, stations, fromID, toID);     
	  
    }
    else if (cmd == "bfs")
    {
      cin >> fromID;
      
      Bfs(DivvyGraph, stations, fromID);
	    
    }
    else if (cmd == "debug")
    {
      DivvyGraph.PrintGraph("Divvy Graph");
    }
    else
    {
      cout << "**Invalid command, try again..." << endl;
    }

    cout << ">> ";
    cin >> cmd;
  }

  cout << "**Done**" << endl;
  return 0;
}
