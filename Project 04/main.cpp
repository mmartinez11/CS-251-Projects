/*main.cpp*/
//
// This project utilizes avl trees in order to create a database that can access using a query entry.
// The main.cpp file has functions that allow it to read meta and data files and create avl trees based on the meta file.
// Each indexed tree can be then searched to find the offset position of valued in the data file 
//
// <<Manuel M Martinez>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>

#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}

//Given an empty AVL Tree it will store all the offset positions as values and an indexed column as a key 
void buildTree(vector<avltree<string, streamoff>>& tree, int matchColum, string tablename, int numColumns, int recordSize)
{
	
	//Open file and make sure it opens 
	string fileName = tablename + ".data";
	
	ifstream fileData(fileName, ios::in | ios::binary);
	
  if(!fileData.good())
  {
    cout << "**Error: couldn't open meta file '" << fileName << "'." << endl;
    return;
  }
	
	
	fileData.seekg(0, fileData.end);  // move to the end to get length of file:
    streamoff length = fileData.tellg();
	
	streamoff pos = 0;  // first record at offset 0:
    string value;
	
  //Loop throught the whole length of the file 	
  while (pos < length)
  {
    fileData.seekg(pos, fileData.beg);  // move to start of record:

    for (int i = 0; i < numColumns; ++i)  // read values, one per column:
    {
		fileData >> value;
      
		//When the indexed column is reached insert key and position in tree 
		if(i == matchColum)
		{
			
		tree[matchColum].insert(value, pos);	
			
		}
		
    }

    pos += recordSize;  // move offset to start of next record:
  }
}

//Display information on indexed trees such as height and size 
void displayInfo(vector<avltree<string, streamoff>> myTree, vector<int> index, vector<string> names, int numColumns)
{
	//Loop through each tree 
	for(int i = 0; i < numColumns; i++)
	{
		//Only display non-empty trees that are empty
		if(index.at(i) == 1)
		{
			cout << "Index column: " << names.at(i) << endl;
			cout << "  Tree size: " << myTree[i].size() << endl;
			cout << "  Tree height: " << myTree[i].height() << endl;
		}	
	}
}

//Checks for errors in query entry and displays error messages in console 
bool errorCheck(vector<string> tokens, vector<string> names, string tablename)
{
		//if first key word is not select then theres an error 
		if(tokens.at(0) != "select")
		{
			
			cout << "Unknown query, ignored..." << endl;
			return false;
			
		}
		
		//If certain keywords are not in the right spot then theres an error 
		if(tokens.at(2) != "from" || tokens.at(4) != "where" || tokens.at(6) != "=")
		{
			cout << "Invalid select query, ignored..." << endl;
			return false;
		}
	
		//If tablename is not the same then there is an error 
		if(tokens.at(3) != tablename)
		{
			cout << "Invalid table name, ignored..." << endl;
			return false;
		}
	
	//Token 1 is select column		
	int val = 1;
	
	//Loops through 2 tokens 
	for(int j = 0; j < 2; j++)
	{
			//Loops through all column names 
			for(unsigned int i = 0; i < names.size(); i++)
			{
				//If select column is equal to '*' or a valid column name
				//Then there is no error  
				if(tokens.at(val) == names.at(i))
				{
					break;
				}
				else if(j == 0 && tokens.at(val) == "*")
				{
					break;
				}
				
				//If the above if statements are not triggered before the loop reaches its end then there 
				//is an error 
				if(i == names.size() - 1)
				{
					if(j == 0)
					{
						cout << "Invalid select column, ignored..." << endl;	
					}
					else 
					{
						cout << "Invalid where column, ignored..." << endl;
					}
					return false;
				}
		
			}
		
		//Token 5 is where column
		val = 5;
	}
	
	//Checks if both where and select columns are the same and gives and error 
	if(tokens.at(1) == tokens.at(5))
	{
		cout << "Invalid both were and select columns are the same..." << endl;
		return false;
	}
		
	//If no main error statements are true then there are no errors in query entry 
	return true;
}

int main()
{
  string tablename; // = "students";

  cout << "Welcome to myDB, please enter tablename> ";
  getline(cin, tablename);

  cout << "Reading meta-data..." << endl;
  
	
	//Meta Data Values 
	int recordSize;  
	int numColumns; 
	
	string columnName;
	
	int indexValue; 
	
	//Vectors to sote the Meta data indexes and their respective names 
	vector<int> index;
	vector<string> names;
	
	//Make a new string that contains the META DATA name 
	string metaName = tablename + ".meta";
	
	//Read From the META DATA 
	ifstream metaData(metaName, ios::in | ios::binary);
	
	//Check if the META FILE DOES OPEN 
  if (!metaData.good())
  {
    cout << "**Error: couldn't open meta file '" << metaName << "'." << endl;
    return 0;
  }
	
     //Read from META FILE 
	 metaData >> recordSize;
	 metaData >> numColumns;

 //Read Meta File and push_back index values and names into vectors 	
 while(!metaData.eof())
 {
	 metaData >> columnName;
	 names.push_back(columnName);

	 metaData >> indexValue;
	 index.push_back(indexValue);
	 
 }
	
  cout << "Building index tree(s)..." << endl;
	
	//Make a vector that stores a # of empty avl trees. 
	//Each individual index points to a UNIQUE avl tree.
	vector<avltree<string, streamoff>> myTree(numColumns);
	
	//Build a tree based on indexed columns 
	for(int i = 0; i < numColumns; i++)
	{
		//If the column is index build a tree 
		if(index.at(i) == 1)
		{
			buildTree(myTree, i, tablename, numColumns, recordSize);
		}
		
	}
	
	//Display tree info about each built tree 
	displayInfo(myTree, index, names, numColumns);
	

 // Main loop to input and execute queries from the user:
 string query;
  
  cout << endl;
  cout << "Enter query> ";
  getline(cin, query);

  //Query entry loop 
  //If Exit is input then it will end the program 
  while (query != "exit")
  {
	
	//Vector will store the Query entry in parts (strings)
    vector<string> tokens = tokenize(query);
    
	//Vector will store values of the data file 
	vector<string> valA;
	  
	//Variable will store position type streamoff
	streamoff* position;

	//Query entry is checked for any errors
	if(errorCheck(tokens, names, tablename))
	{	
		
		//Varibales to store select and where querys 
		int where = -1;
		int select = -1;
		
		//This variable will store query if it is not an index 
		//It will be used when Linear Search is performed 
		int notIndex;
		
		//The purpose of this loop is to assign the column position to our where, select, and notIndex variables
		//This will make it easier to determine were in the file we want to go, what we want to display, and which tree to use  
		//This will also allow less usage of loops 
		for(int i = 0; i < numColumns; i++)
		{
			//If the select column is found then its column position is assigned to 'select'
			if(tokens.at(1) == names.at(i))
			{
				select = i;	
			}
			//If the where column is found then its column position is assigned to 'where'
			if(tokens.at(5) == names.at(i) && index.at(i) == 1)
			{
				where = i;
			}
			//If the where query is not indexed then notIndex will store the column position + 1 
			//b/c we will be using linear search 
			else if(tokens.at(5) == names.at(i) && index.at(i) == 0)
			{
				notIndex = i + 1;
			}
		}
		
		//If the select column is '*' and 'were' is indexed then all the values of the key will be displayed  
		if(tokens.at(1) == "*" && where != -1)
		{
			//Search for value(position) in indexed tree using key 
			position = myTree[where].search(tokens.at(7));
			
			//Check if search returns nullptr
			if(position == nullptr)
			{
				cout << "Not found..." << endl;
				cout << endl;
				cout << "Enter query> ";
				getline(cin, query);
				
				continue;
			}
			
			//Get all values from position
			valA = GetRecord(tablename, *position, numColumns);
			
			//Display all values 
			for(int i = 0; i < numColumns; i++)
			{
				cout << names.at(i) << ": " << valA.at(i) << endl;
				
			}
		}
		//If the select column is not '*' and 'were' is indexed then only a specific value will be looked for and displayed
		else if(tokens.at(1) != "*" && where != -1)
		{
			//Search for value(position) in indexed tree using key 
			position = myTree[where].search(tokens.at(7));
			
			//Check if search returns nullptr
			if(position == nullptr)
			{
				cout << "Not found..." << endl;
				cout << endl;
				cout << "Enter query> ";
				getline(cin, query);
				
				continue;
			}
			
			//Get all values from position
			valA = GetRecord(tablename, *position, numColumns);
			
			//Display value
			for(int i = 0; i < numColumns; i++)
			{
				//Once column position is found it displays the value and its name 
				if(i == select)
				{
					cout << names.at(i) << ": " << valA.at(i) << endl;
				}
				
			}
		}
		//If the select column is '*' and 'were' is not-indexed then all values will be looked for and displayed 
		else if(tokens.at(1) == "*" && where == -1)
		{
			//First Linear search must be used to retrive the offset positions and are stored in vector valB
			vector<streamoff> valB = LinearSearch(tablename, recordSize, numColumns, tokens.at(7), notIndex);
			
			//Checks if nothing is returned inside the vector
			if(valB.empty())
			{
				cout << "Not found..." << endl;
				cout << endl;
				cout << "Enter query> ";
				getline(cin, query);
				
				continue;
			}
			
			//Loop through the positions stored in valB and display all the values at each position 
			for(unsigned int i = 0; i < valB.size(); i++)
			{
				//Get all values at the current position
				valA = GetRecord(tablename, valB.at(i), numColumns);
				
				//Display all values at that position
				for(int i = 0; i < numColumns; i++)
				{
					cout << names.at(i) << ": " << valA.at(i) << endl;
				
				}
			}
		}
		//If the where column is not indexed and the select column is not '*' then linear search is used 
		else
		{	
			//Linear search is used to retrive the offset positions and are stored in vector valB
			vector<streamoff> valB = LinearSearch(tablename, recordSize, numColumns, tokens.at(7), notIndex);
			
			//Checks if nothing is returned inside the vector
			if(valB.empty())
			{
				cout << "Not found..." << endl;
				cout << endl;
				cout << "Enter query> ";
				getline(cin, query);
				
				continue;
			}
			
			//Loop through the positions stored in valB and display the values asked for at each position
			for(unsigned int i = 0; i < valB.size(); i++)
			{
				//Get all values at the current position
				valA = GetRecord(tablename, valB.at(i), numColumns);
				
				//Display asked for values at that position
				for(int j = 0; j < numColumns; j++)
				{
					if(j == select)
					{
						cout << names.at(j) << ": " << valA.at(j) << endl;
						
					}
				}
				
			}
			
		}
			
	}
	  
	    
	//Get next query entry 
    cout << endl;
    cout << "Enter query> ";
    getline(cin, query);
  }
  
  return 0;
}


