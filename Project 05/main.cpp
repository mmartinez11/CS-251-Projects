/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     <<Manuel M Martinez>>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;

//Swap function. Swap not only plate names but also their conrresponding values 
void swap(vector<string>& plates, vector<int>& amounts, unsigned int xp, unsigned int yp)  
{  
	//Swap Plates
    string temp = plates[xp];  
    plates[xp] = plates[yp];  
    plates[yp] = temp;
	
	//Swap Plate Values
	int temp1 = amounts[xp];  
    amounts[xp] = amounts[yp];  
    amounts[yp] = temp1;
}

//Bubble sort function 
void bSort(vector<string>& plates, vector<int>& amounts)
{
	//Untility variables
	unsigned int i;
	unsigned int j;
	
	//Get size of the plates vector 
	unsigned int n = plates.size();
	
	//First Loop
	for (i = 0; i < n-1; i++)
	{
		//Second Loop  
		for (j = 0; j < n-i-1; j++)
		{
			//If if plate at J is bigger than plater at J+1 then swap 
			if(plates[j] > plates[j+1])
			{
			    swap(plates, amounts, j, (j+1));
			}
		}
	}
  
	
}

// hashInput:
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;


  // process input file of fines and license plates:
  hashInput(basename, hashplates);
	
	//Create/Open Output Text file 
	ofstream outfile;
    outfile.open(basename + "-output.txt");	
	
  //Get Plates and Values from AVL Tree 	
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();
	
  //Sort Plates and Values 	
  bSort(plates, amounts);
  cout << "Sorting..." << endl;
  cout << "Writing '";
  cout << basename << "-output.txt'..." << endl;	

  //Write into Output Text file the sorted Plates and Values 
  for (size_t i = 0; i < plates.size(); ++i)
  {
    outfile << "\"" << plates[i] << "\"" << " $" << amounts[i] << endl;
  }

	 //Close Ouput Text file 
     outfile.close();
	
	
  // done:
  
  return 0;
}