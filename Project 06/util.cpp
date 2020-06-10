/*util.cpp*/
//
//<Manuel M Martinez> CS 251 Fall 2019 UIC
//The purpose of this util.cpp file is to implement each of the algorithms. Dijkstra, DFS, and BFS
//are all implemented in individual functions. These functions are called by main and are then used  
//based on the starting vertex the user has chosen.
//
//



#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <limits> 

#include "graph.h"
#include "util.h"

#include "minqueue.h"
#include "arr.h"


using namespace std;
 
//Stores the paths from each vertex that can be reached from the starting vertex
//These will be stored in a vector inside each class 
void storePrev(myArray* dpa, const vector<char>& vTex)
{
	//Utility Variables to store indexes
	int a;
	int b;
	int c;
	
	//Check each vertex in the graph
	for(unsigned int i = 0; i < vTex.size(); i++)
	{
		//Get the first index 
		a = vTex.at(i) - 'A';
		b = vTex.at(i) - 'A';
		
		//If a vertex cannot be reached then it will not be modified 
		if(dpa[a].getDistance() != Infinity)
		{
			//Push back the first vector name into the vector in the class 
			dpa[a].setVprev(dpa[a].getVx());
			
			//Check the previous index of the current vertex
			//If not = to -1 then its path keeps going 
			while(dpa[b].getPrev() != -1)
			{
				//Set C as the previous index of the vertex
				c = dpa[b].getPrev();
				
				//Push back the vertex into the vector
				dpa[a].setVprev(dpa[c].getVx());
				
				//Set b to c to check if the path continues 
				b = c;
				
			}
					
		}
			
		
	}
	
}

//Sort each vertex based on distance and return a vector that has individual 
//pointers to each class istance used by a vertex 
vector<myArray> sortVertices(myArray* dpa, const vector<char>& vTex)
{
	//Create a minqueue
	minqueue<char, int> a;
	
	//Create a myArray vector
	vector<myArray> c;
	
	//Index variable 
	int b;
	
	//Loop through each vertex in graph
	for(unsigned int i = 0; i < vTex.size(); i++)
	{
		//Get the index of tha vertex
		b = vTex.at(i) - 'A';
		
		//Only store in minqueue if its reachable by the starting vertex
		if(dpa[b].getDistance() != Infinity)
		{
			a.pushinorder(dpa[b].getVx(), dpa[b].getDistance());
		}
	}
	
	//Now since each vertex is sorted based on distance 
	//Loop through minqueue and store them into a vector
	while(!a.empty())
	{
		//Get Index of vertex
		b = a.minfront() - 'A';
		
		//Store each class instance into vector c 
		c.push_back(dpa[b]);
		
		//Pop minqueue
		a.minpop();
	}
	
	//Return vector
	return c;
}

//Dijkstra Algorithm
vector<myArray> DJK(char startV, graph& g)
{
	//Get all the vertices from the graph
	vector<char> vTex;
	vTex = g.vertices();
	
  //Creates an array of pointers in which each pointer points at a class instance  	
  myArray* dpa;
  int N = g.numvertices();
  dpa = new myArray[26];
	
  //Variables used to store the indexes of the array  	
  int a;
  int b;
	
  //minqueue to sort the vertices based on distance from starting vertex	
  minqueue<char, int> unvisitedQueue;	
	
  //Initialize starting values for each vertex	
  for(int i = 0; i < N; i++)
  { 
	  //Get Index of vertex
	  a =  vTex.at(i) - 'A';
	  
	  dpa[a].setDistance(Infinity);
	  dpa[a].setPrev(-1);
	  dpa[a].setVx(vTex.at(i));
 
	  unvisitedQueue.pushinorder(vTex.at(i), Infinity);
  }
	
	 //Change the Distance of the starting Vertex 
	 unvisitedQueue.pushinorder(startV, 0);
	 a = startV - 'A';
	 dpa[a].setDistance(0);
	
	//Utility varibales
	char currentV;
	vector<char> adjacent;
	
	int edgeWeight;
	int alternativePathDistance;
	
	//Main Algorithm Loop. Check if queue is empty
	while(!unvisitedQueue.empty())
	{
		//store current vertex into minqueue
		currentV = unvisitedQueue.minfront();
		unvisitedQueue.minpop();
		
		//Index for current Vertex
		a = currentV - 'A';
		
		//Check if its a reachable vertex
		if(dpa[a].getDistance() == Infinity)
		{
			break;
		}
		
	    //Get adjacent vertices of current vertex
		adjacent = g.neighbors(currentV);
		
		//Check each individual adjacent vertex
		for(unsigned int i = 0; i < adjacent.size(); i++)
		{
			//Get edgeWeight of the current vertex and adjacent vertex
			edgeWeight = g.getweight(currentV, adjacent.at(i));
			
			//Add edgeweight to current distance of vertex
			alternativePathDistance = dpa[a].getDistance() + edgeWeight;
			
			//Index for adjacent Vertex
			b = adjacent.at(i) - 'A';
			
			//Check if alternative Path Distance is less than the distance that the current vertex holds
			if(alternativePathDistance < dpa[b].getDistance())
			{
				//If true set a new distance to the vertex
				dpa[b].setDistance(alternativePathDistance);	
				dpa[b].setPrev(a);
				
				//Store adjacent vertex into minqueue and update its distance
				unvisitedQueue.pushinorder(adjacent.at(i), alternativePathDistance);
			}
			
		}
		
		
	}
	
	//Store the paths from each vertex that can be reached from the starting vertex
	storePrev(dpa, vTex);
	
	//Sort each vertex based on distance and return a vector that has individual 
	//pointers to each class istance used by a vertex 
	vector<myArray> sortedL = sortVertices(dpa, vTex);
	
	return sortedL;
}

// DFS:
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
vector<char> DFS(graph& g, char startV)
{
  //Utility data structures	
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  //Utility varibales	
  char currentV;
  char v1;
 
  //Vector to store adjacent vertices
  vector<char> adjacent;
  
  //store starting vertex into both a set and stack 
  frontierStack.push(startV);
  visitedSet.insert(startV);
  
  //Main Loop. Check if stack is empty
  while(!frontierStack.empty())
  {
	  //set new current vertex
      currentV = frontierStack.top();
      frontierStack.pop();  
     
	  //set current vertex as visited
      visited.push_back(currentV);
      
	  //Get the adjacent vertices of the current vertices
      adjacent = g.neighbors(currentV);
      
	  //Check each individual adjacent vertex
      for(unsigned int i = 0; i < adjacent.size(); i++)
      {
         v1 = adjacent.at(i);
         
		 //If adjacent vertex has not been visited then push and insert
         if(visitedSet.find(v1) == visitedSet.end())
         {
            frontierStack.push(v1);
            visitedSet.insert(v1);  
         }
      }
  }
  
  return visited;
}

// BFS:
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
vector<char> BFS(graph& g, char startV)
{
  
  //Utility data structures 	
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;

  //Utility varibales
  char currentV;
  char v1;
  
  //vector to store adjacent vertices
  vector<char> adjacent;
  
  //Push into queue starting vertex
  frontierQueue.push(startV);
	
  //Insert starting vertex into set 	
  discoveredSet.insert(startV);
  
  //Main loop. Check if queue is empty
  while(!frontierQueue.empty())
  {
	  //Set new current vertex
      currentV = frontierQueue.front();
      frontierQueue.pop();  
     
	  //Push current vertex
      visited.push_back(currentV);
      
	  //Get adjacent vertices of current vertex
      adjacent = g.neighbors(currentV);
      
	  //Loop checks each adjacent vertex
      for(unsigned int i = 0; i < adjacent.size(); i++)
      {
         v1 = adjacent.at(i);
         
		 //If vertex has not been discovered it is set as discovered
         if(discoveredSet.find(v1) == discoveredSet.end())
         {
            frontierQueue.push(v1);
            discoveredSet.insert(v1);
         }
      }
  }
  
  //Returns all the vertices that have been visited
  return visited;
}

// BuildGraph:
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
// vertex vertex vertex ... #
// src dest weight ... #
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  // Input vertices as single uppercase letters:  A B C ... #
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  // Now input edges:  Src Dest Weight ... #
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}

