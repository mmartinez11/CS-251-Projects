/*main.cpp*/

//
//main.cpp is used for to read and create a graph from a file.
//It also runs DFS and BFS when a vertex is selected by the user.
//It then displays the results of each algorithm in addition to 
//the neighbors of said vertex. Furthermore it runs the Dijkstra algorithm
//and shows the results.  
// 
//<Manuel M Martinez>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <stack>

#include "graph.h"
#include "util.h"

#include "arr.h"
#include "minqueue.h"

using namespace std;

//Outputs the vertex values, the weight value, and the edges of the created graph
void outputGraph(graph& g)
{
  //Gets graph vertices
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  //Shows vertices
  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  //Shows edges
  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
}

//Stores the sorted vertices of the vector Dijk 
vector<char> getSVX(const vector<myArray>& Dijk)
{
	//Vector to store vertices
	vector<char> sortedVx;
	
	//Create a class intance that is assigned the values of the pointer class 
	myArray pointD;
	
	//Loop to store vertices into new char vector
	for(unsigned int i = 0; i < Dijk.size(); i++)
	{
		//Get individual pointer from vector 
		pointD = Dijk.at(i);
		
		sortedVx.push_back(pointD.getVx());
	}
	
	//Return vector 
	return sortedVx;
}

//Ouput the basic results for each individual algorithm
void ouputResults(const vector<char>& Ouput, string algorithm)
{
	  //Display the type of algorithm type 
	  cout << algorithm << ": ";

	  //Display Results 
      for (char v : Ouput)
	  {
        cout << v << " ";
	  }
	
      cout << endl;
	
}

//Show the distance via the vertices of the given vertex 
void showDijK(const vector<myArray>& Dijk)
{
	//Create a instance of a class
	myArray pointD;

	//Display the distance via vertices of the given vertex
	for(unsigned int i = 0; i < Dijk.size(); i++)
	{
		pointD = Dijk.at(i);
		
		cout << " " << pointD.getVx() << ": " << pointD.getDistance() << " Via ";
		pointD.showPrev();
		cout << endl;
		
	}
	
}

//main 
int main()
{
  //Utility variables 
  graph  g;
  string filename;
  char   startV;

  //Ask for the file to be opened 
  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //Functions to input and output the graph 
  buildGraph(filename, g);
  outputGraph(g);

  
  //Ask the user for a starting vertex so it can be run through 
  //3 different algorithms
  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;

  //Main Loop 
  while (startV != '#')
  {
	//Vectors to store the results of both DFS and BFS 
    vector<char> dfsVisited;
	vector<char> bfsVisited;
	 
	//Vector to store the vertices of the starting vertex   
	vector<char> neighbors;
	  
	//Stores the sorted vertices of the Dijkstra algorithm 
	vector<char> SortVx;
	  
	//Stores the pointers to a class instance of each vertex that
	//can be reached via the starting vertex  
	vector<myArray> Dijk;
	  
	//String variable to store name of algorithm  
	string algorithm;  
	
	//Check if Vertex is found in the graph
	if(g.isvertex(startV))
	{
		//First show the neighbors of the starting vertex
		algorithm = "Neighbors"; 
		neighbors = g.neighbors(startV);//Get Neighbors
		ouputResults(neighbors, algorithm);//Show Neighbors
		
		//Show BFS vertices
		algorithm = "BFS";
		bfsVisited = BFS(g, startV);//Get BFS vertices
		ouputResults(bfsVisited, algorithm);//Show BFS vertices
		
		//Show DFS vertices
		algorithm = "DFS";
		dfsVisited = DFS(g, startV);//Get DFS
		ouputResults(dfsVisited, algorithm);//Show DFS vertices
		
		//Show Dijkstra vertices
		algorithm = "Dijkstra";
		Dijk = DJK(startV, g);//Get Dijkstra
	    SortVx = getSVX(Dijk);//Ger sorted vertices
		ouputResults(SortVx, algorithm);//Show Dijkstra vertices
		showDijK(Dijk);//Show the distance of each Dijkstra vertices
		
	}
	else
	{
	   cout << "Not a vertex in graph, ignored..." << endl;
	}
	  
    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }
	
	
	
  //
  // done
  //
  return 0;
}
