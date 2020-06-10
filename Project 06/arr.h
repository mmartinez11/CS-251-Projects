//<Manuel M Martinez> CS 251 Fall 2019 UIC 
//
//This class is used to store the distance of each vertex that can be reached by the starting vertex.
//In addition the class stores the index for the previous vertex. Also stores the char name of the vertex.
//Furthermore the path from the starting vertex to a specific vertex is stored in a vector. This is to 
//make showing the path of starting vertex to a specific vertex much easier.
//SideNote: The reason why I chose the class to be named "myArray" is because an array of pointers is created
//in util.cpp that creates N amount of instances of this class   
//

#pragma once 

#include <iostream>
#include <limits> 
#include <vector>

using namespace std;

//Set Infinity as a constant global variable 
const int Infinity = numeric_limits<int>::max();

//Class myArray
class myArray{

	//Private data members 
	private:
	
		int Distance;
		int Previous;
		char Vertex;
	
		vector<char> PrevList;
	
	//Public class functions 
	public: 

	//Default constructor 
	myArray()
	{
		Distance = Infinity;
		Previous = -1;
		Vertex = '@';	
	}
		
	//Set Distance of vertex
	void setDistance(int distance)
	{
		Distance = distance;
	}

	//Set previous index value of vertex
	void setPrev(int previous)
	{
		Previous = previous;
	}
	
	//Set char name of vertex
	void setVx(char vertex)
	{
		Vertex = vertex;
	}
	
	//Push back verticies that are part of the path between
	//the starting vertex and a specific vertex
	void setVprev(char a)
	{
		PrevList.push_back(a);
	}
	
	//Get vertex distance
	int getDistance()
	{
		return Distance;
	}

	//Get the previous vertex index 
	int getPrev()
	{
		return Previous;
	}
	
	//Get the vertex char name 
	char getVx()
	{
		return Vertex;
	}
	
	//Show the path between the starting vertex and a specific vertex
	void showPrev()
	{
		int i = PrevList.size() - 1;
		
		while(i != -1)
		{
			cout << PrevList.at(i) << " ";
			i--;
		}
	}
	
};