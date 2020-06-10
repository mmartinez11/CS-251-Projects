/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Manuel M Martinez>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>

#include "ILplates.h"

using namespace std;


//Error checking Function 
int validPlatCheck(string plate)
{
	
  //Utility variables
  char space = ' ';
  int asciiVal;
  int digitL;
	
  //Find the first space
  int postion1 = plate.find(space);
  
  //Check if there is more than one space
  int postion2 = plate.rfind(space);
   	
  //Check if its is personalized
  if(postion1 == postion2 && postion1 != -1 && (plate.length() > 2 && plate.length() < 9))
  {
	  //Calculate if it has 2 digits or 1 digit at the end of the plate  
	  digitL = (plate.length() - 1) - postion1;
	 
	  //Check if its either 1-5 or 6 Letter format and check numbers 
	  if(1 <= postion1 && postion1 <= 5)
	  {
		 //Check for the appropriate amount of values
		 if(digitL == 1 || digitL == 2)
		 {
			 
			  //Check if all characters before space are capital Letters
			  for(int i = 0; i < postion1; i++)
			  {
				asciiVal = int(plate.at(i));	  
		
				if(asciiVal < 65 || asciiVal > 90)
				{
					return -1;
				}
			  }
			 
			 //Check if final digit for 1-5 Letter plate matches the appropriate specifications (ie. 1-9)
			 if(digitL == 1 && (plate.at(postion1 + 1) >= 49 && plate.at(postion1 + 1) <= 57))
			 {
				 //Hash PLATE// 
				 return 1;
			 }
			 //Check if final digits for 6 Letter plate matches the appropriate specifications (ie. 1-9 and 0-9)
			 else if(digitL == 2 && (plate.at(postion1 + 1) >= 49 && plate.at(postion1 + 1) <= 57) && (plate.at(postion1 + 2) >= 48 && plate.at(postion1 + 2) <= 57))
			 {
				 //Hash PLATE// 
				 return 1;
			 }
			 else 
			 {
				 //Not valid
				 return -1;
			 }
			 
		 }
		 else
		 {
			return -1;
		 }
	       
	  }
	  else if(postion1 == 6)
	  {
		//Check for the appropriate amount of values
		 if(digitL == 1)
		 {
			 
			  //Check if all characters before space are capital Letters
			  for(int i = 0; i < postion1; i++)
			  {
				asciiVal = int(plate.at(i));	  
		
				if(asciiVal < 65 || asciiVal > 90)
				{
					return -1;
				}
			  }
			 
			 if(digitL == 1 && (plate.at(postion1 + 1) >= 49 && plate.at(postion1 + 1) <= 57))
			 {
				 //Hash PLATE // 
				 return 1;
			 }
			 else
			 {
				 return -1;
			 }
			 
			 
		 }
		 else
		 {
			return -1;
		 }  
		  
	  }
	  else
	  {
		  return -1;
	  }
	  
  }
  //It is VANITY Plate 	
  else
  {
	  //Check if plate matches length specifications
	  if(plate.length() > 0 && plate.length() < 8)
	  {
		  //Take the first char value of Vanity Plate 
		  asciiVal = int(plate.at(0));
		  
		  //Check if its num or alpha plate
		  //Is Alpha Plate
		  if(asciiVal >= 65 && asciiVal <= 90)
		  {
			  asciiVal = 0;
			  
			  //Check if alpha plate is 1 through 7 letters 
			  if(plate.length() > 0 && plate.length() < 8)
			  {
	              //Check if letters are all capital letters 
				  for(unsigned int i = 0; i < plate.length(); i++)
			      {
				     asciiVal = int(plate.at(i));	  
		
				     if(asciiVal < 65 || asciiVal > 90)
					{
						return -1;
					}
				  }
				  
				  //Hash the Alpha Vanity PLATE
			      return 2;
				  
			  }
			  else
			  {
				  return -1;
			  }
		  }
		  //Is Number Plate 
		  else if(asciiVal >= 48 && asciiVal <= 57)
		  {
			  asciiVal = 0;
			  
			  //Check if number plate matches length specifications
			  if(plate.length() > 0 && plate.length() < 4)
			  {
				  //Check if plate is valid numbers 
				  for(unsigned int i = 0; i < plate.length(); i++)
			      {
				     asciiVal = int(plate.at(i));	  
		
				     if(asciiVal < 48 || asciiVal > 57)
					{
						return -1;
					}
				  }
				  
				  //Hash the Vanity PLATE
			       return 2;
				  
			  }
			  else
			  {
				  return -1;
			  }
		  }
		  else
		  {
			  return -1;
		  }
		 
	  }
	  else
	  {
		  return -1;
	  }
  }
	
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
  unsigned long long index = -1;

  //Utility Variables 
  int errorToken = validPlatCheck(plate);
  char space = ' ';
  int postion;
	
  unsigned long long asciiVal;
  int numInt;
	 	
	
   //Personalized Plate
  if(errorToken == 1)
  {
	 index = 0;
	  
	 //Find location of space in string 
	 postion = plate.find(space);
	   
	 //Hashing The Letters First Using Loop  
	 for(int i = 0; i < postion; i++) 
	 {
	    if(i == 0) 
	    {
		 //Getting first letter of Plate 
		 asciiVal = int(plate.at(i)) - 65 + 1;
		 asciiVal = asciiVal * 1000; 
		 
		 index = index + asciiVal;
	    }
	    else
	    {
			//Adding ascii value of Letter to index 
	        asciiVal = int(plate.at(i));
	        index = index + asciiVal;
	    }
		 
	    //Adding Position of Letter in alphapet to index 
	    index = index + (int(plate.at(i)) - 49 + 1);
	 }
	  
	  //Calculating how many digits are in plate 
	  numInt = plate.length() - (postion + 1);
	  
	  if(numInt == 1)
	  {
		  //Add the value of digit to index 
		  index = index + int(plate.at(postion + 1)) - 49 + 1;
	  }
	  else
	  {
	      //Getting the first number of the plate 
		  int val1 =int(plate.at(postion + 1)) - 49 + 1;
		  val1 = val1 * 10;
		  
		  //Getting the second number of the plate 
		  int val2 = int(plate.at(postion + 2)) - 49 + 1;
		  
		  //If the second number is zero then it will equall the ascii value of the first letter
		  if(val2 == 0)
		  {
			  val2 = int(plate.at(0));
		  }
		  
		  //Add the two digits to the index
		  index = index + (val1 + val2);
		  
		  //Add length of Plate to further make index unique 
		  index = index + plate.length();
	  }
	  
	  
  }
  //Vanity Plate
  else if(errorToken == 2)
  {
	  index = 0;
	  
	  //Check for number or letter as the first value  
	  asciiVal = int(plate.at(0));
	  
	  //Is Number Plate 
	  if(asciiVal >= 48 && asciiVal <= 57)
	  {
		  //Subtract index value from size of hashtable 
		  index = stoi(plate); 
		  index = HT.Size() - index;
	  }
	  //Is Letter Plate  
	  else
	  {
		  index = 0;
		  
		  //Add the ascii value of each letter to the index 
		  for(unsigned int i = 0; i < plate.length(); i++)
		  {
			 asciiVal = int(plate.at(i)); 
		 
			 index = index + asciiVal;
		 
		  }
		 
		  //Set the region of the letter plate index to less than the region of the number plate indexes
		  index = (HT.Size() - 999) - index;
	  }
	 
  }
  //Plate contains errors
  else
  {
	  return -1;
  }
 
  int result = index % HT.Size();
	
  return result;
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
	
	//Utility Variables
	int bucketsProbed = 0;
	int index = 0;
	
	//Hash Plate and get index 
	index = Hash(plate);
	
	//Variables from hashtable
	bool empty;
	string key; 
	int value;
	
	//Get variables from hashtable
	HT.Get(index, empty, key, value);
	
	//Search For Value in hashtable 
	while(bucketsProbed < HT.Size() && empty == false)
	{
		
		if(empty == false && key == plate)
		{
			return value;	
		}
		
		
		index = (index + 1) % HT.Size();
		HT.Get(index, empty, key, value);
        ++bucketsProbed;
		
	}
	
  return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  
	//Utility Variables
	int bucketsProbed = 0;
	int index = 0;
	index = Hash(plate);
	
	//Variables from hashtable
	bool empty;
	string key; 
	int value;

	while(bucketsProbed < HT.Size())
	{
		//Get the values of the hashtable 
		HT.Get(index, empty, key, value);
		
		//Bucket is empty
		if(empty == true)
		{
			HT.Set(index, plate, newValue);
			
			break;
		}
		//Bucket needs fine(value) to be updated
		else if(empty == false && key == plate)
		{
			HT.Set(index, plate, newValue);
			
			break;
		}
			
		index = (index + 1) % HT.Size();
   
        ++bucketsProbed;
	}
	
	
}
