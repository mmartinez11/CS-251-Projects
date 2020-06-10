//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string> 
#include <ctype.h>
#include <stdio.h>
#include "bst.h"

using namespace std; 

//Struct is used to store all the information on each individual movie
struct MovieData
{
	int id; 
	string name;
	int pubYear;
	
	int Num5Stars = 0;
	int Num4Stars = 0;
	int Num3Stars = 0;
	int Num2Stars = 0;
	int Num1Stars = 0;
	
	double avgRating = 0;
		
};


// trim
// trims whitespace from beginning and end of string.
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}

void getReviews(string reviewsFilename, MovieData &movieInfo)
{
	   int reviewId = 0;	
	   int id = 0;
	   int rating = 0;
	
      movieInfo.Num5Stars = 0; 
	  movieInfo.Num4Stars = 0; 
	  movieInfo.Num3Stars = 0; 
	  movieInfo.Num2Stars = 0; 
	  movieInfo.Num1Stars = 0; 
	
      ifstream reviewsFile(reviewsFilename);
	
	  reviewsFile >> reviewId;
	  
	
	while(!reviewsFile.eof())
	{
	
		
		reviewsFile >> id; 
		
		reviewsFile >> rating;
		
		if(id == movieInfo.id)
		{
			if(rating == 5)
			{
				movieInfo.Num5Stars++;
			}
			else if(rating == 4)
			{
				movieInfo.Num4Stars++;
			}
			else if(rating == 3)
			{
				movieInfo.Num3Stars++;
			}
			else if(rating == 2)
			{
				movieInfo.Num2Stars++;
			}
			else if(rating == 1)
			{
				movieInfo.Num1Stars++;
			}
					
		}
		
		
		reviewsFile >> reviewId;
	}
	
	
	
}
// InputMovies
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
void InputMovies(string reviewsFilename, string moviesFilename, binarysearchtree<int, MovieData> &bst1, binarysearchtree<string, MovieData> &bst2)
{
  struct MovieData movieInfo;
	
  ifstream moviesFile(moviesFilename);
  double sum = 0;
  double average = 0; 
  
 
  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> movieInfo.id;  // get first ID, or set EOF flag if file empty:
  
  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> movieInfo.pubYear;
    getline(moviesFile, movieInfo.name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    movieInfo.name = trim(movieInfo.name);  
   
	  
	getReviews(reviewsFilename, movieInfo);
    
	movieInfo.avgRating = 0;
	  
	sum = movieInfo.Num1Stars + movieInfo.Num2Stars + movieInfo.Num3Stars + movieInfo.Num4Stars + movieInfo.Num5Stars;   
	average = (movieInfo.Num1Stars * 1) + (movieInfo.Num2Stars * 2) + (movieInfo.Num3Stars * 3) + (movieInfo.Num4Stars * 4) + (movieInfo.Num5Stars * 5);  
	  
	movieInfo.avgRating = average / sum; 
	  
	bst1.insert(movieInfo.id, movieInfo);
	bst2.insert(movieInfo.name, movieInfo);

    moviesFile >> movieInfo.id;  // get next ID, or set EOF flag if no more data:
  }
	
	
}


//
// main
//
int main()
{
  binarysearchtree<int, MovieData> bst1;
  binarysearchtree<string, MovieData> bst2;
	
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  InputMovies(reviewsFilename, moviesFilename, bst1, bst2);

//---------------------------------------------------------

	
	int x;
	int y;
	int z;
	
	int w = 0;
	ifstream reviewsFiles(reviewsFilename);
	reviewsFiles >> x;

	while(!reviewsFiles.eof())
	{
	   
		
		reviewsFiles >> y;
		
		
		
		reviewsFiles >> z;
		
		w++;
		
		
		reviewsFiles >> x;
		
	}
	
	cout << "Num movies: " << bst1.size() << endl;
	cout << "Num reviews: " << w << endl;
	
	cout << endl;
	
	cout << "Tree by movie id: " <<  "size=" << bst1.size() << ", "
         << "height=" << bst1.height() << endl;
	cout << "Tree by movie name: " <<  "size=" << bst2.size() << ", "
         << "height=" << bst2.height() << endl;
	cout << endl;
	
//------------------------------------------------------------	

  string user;
  int movId;
  cout << "Enter a movie id or name (or # to quit)>";
  getline(cin, user);
  //int length = user.length();
	
  while(user != "#")
  {
	
	struct MovieData *ptr;
//for(int i = 0; i < length; i++)
	
	if(isalpha(user[0]) != 0)
	{
	ptr = bst2.search(user);
	
	if(ptr == nullptr)
	{
		cout << "Not found..." << endl;
		cout << endl;
		cout << "Enter a movie id or name (or # to quit)> ";
        getline(cin, user);
		continue;
	}
 
	}
	else
	{
	movId = std::stoi(user);
	ptr = bst1.search(movId);
	
	if(ptr == nullptr)
	{
		cout << "Not found..." << endl;
		cout << endl;
		
		cout << "Enter a movie id or name (or # to quit)> ";
        getline(cin, user);
		
		continue;
	}
		
	}
	
	
    cout << "Movie ID: " << ptr->id << endl;  
	cout << "Movie Name: " << ptr->name << endl;
	cout << "Avg rating: " << ptr->avgRating << endl;
	cout << "5 stars: " << ptr->Num5Stars << endl;
	cout << "4 stars: " << ptr->Num4Stars << endl;
	cout << "3 stars: " << ptr->Num3Stars << endl;
	cout << "2 stars: " << ptr->Num2Stars << endl;
	cout << "1 stars: " << ptr->Num1Stars << endl;
	cout << endl;  
	  
	cout << "Enter a movie id or name (or # to quit)> ";
    getline(cin, user); 
  }
	
  
 
	
  return 0;
}
