Zakee Jabbar
UIC


"Divvy Bike Analysis w/ Graphs"


This program takes in data on Divvy bikes, stations, and trips and stores them into a graph. After the data is stored, the user can enter different commands to get specific data.

To run this program:

g++ -std=c++11 graph.cpp main.cpp -o myProg
./myProg


The following commands are supported:

1. info stationID
	a. Outputs information on the location of the stations,# of destination stations (number of unique stations where trips originated from this station were ended), number of trips to those destination stations, and a list of all routes along with the number of trips for a specific route.
2. trips fromID toID (gives info on number of trips between two stations)
3. bfs stationID (performs a breadth first search and prints out all the stations visited)
4. debug (prints out the entire graph)
5. exit (quits the program)


Sample User Input:

stations.csv (Other stations file from Data Files folder)
trips.csv (Other trips file from Data Files Folder)
Any of the commands above after the "Ready" message.




