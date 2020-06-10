/*util.h*/
//
//<Manuel M Martinez> CS 251 Fall 2019 UIC
//
//Util.cpp and main.cpp utilize this h file. This h file contains the function calls for 
//the 3 algorithms that are used by the starting vertex.
//

#pragma once

#include <iostream>
#include <string>

#include "graph.h"
#include "arr.h"

using namespace std;

void buildGraph(string filename, graph& g);//Build Graph 
vector<char> DFS(graph& g, char startV);//Perform DFS algorithm
vector<char> BFS(graph& g, char startV);//Perform BFS algorithm

vector<myArray> DJK(char startV, graph& g);//Perform Dijkstras algorithm