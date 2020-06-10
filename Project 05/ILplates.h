/* ILplates.h */

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.  Implementation in associated .cpp
// file.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#pragma once

#include <iostream>
#include <string>

#include "hashtable.h"

using namespace std;

class ILplates
{
private:
  hashtable<string, int>& HT;  // reference to underlying hashtable:

public:
  //
  // constructor
  //
  ILplates(hashtable<string, int>& ht)
    : HT(ht)
  { }

  
  int  Hash(string plate);//Hash Plate 
  int  Search(string plate);//Search for Plate 
  void Insert(string plate, int newValue);//Insert New Plate 
};
