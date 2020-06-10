//
// <<Manuel M Martinez>>
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
struct MovieData{

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
string trim(const string& str){

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

//The purpose of the function is to read(review id, movie id, rating) from the reviews1.txt file and 
//search for and store the reviews for each induvidual movie utilizing the current movie ID from movie1.txt
void getReviews(string reviewsFilename, MovieData &movieInfo)
{
	   //Will store the values of the file (reviews1.txt)
	   int reviewId = 0;	
	   int id = 0;
	   int rating = 0;
	
	  //Every rating is initialized as Zero each time the function is called	
          movieInfo.Num5Stars = 0; 
	  movieInfo.Num4Stars = 0; 
	  movieInfo.Num3Stars = 0; 
	  movieInfo.Num2Stars = 0; 
	  movieInfo.Num1Stars = 0; 
	
          ifstream reviewsFile(reviewsFilename);
	
	  reviewsFile >> reviewId;
	  
	//Loop that stops when the file has been read completely 
	while(!reviewsFile.eof()){

		reviewsFile >> id; 
		
		reviewsFile >> rating;
		
		//If the movie id in review files matches the movie id from movie files that was passed
		//Then the corresponding rating is looked for and increased by one.
		if(id == movieInfo.id){

			if(rating == 5){
			      movieInfo.Num5Stars++;
			}
			else if(rating == 4){
			      movieInfo.Num4Stars++;
			}
			else if(rating == 3){
			      movieInfo.Num3Stars++;
			}
			else if(rating == 2){
			     movieInfo.Num2Stars++;
			}
			else if(rating == 1){
			     movieInfo.Num1Stars++;
			}
					
		}
		
		reviewsFile >> reviewId;
	}
	
}

// InputMovies
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:id pubYear name
void InputMovies(string reviewsFilename, string moviesFilename, binarysearchtree<int, MovieData> &bst1, binarysearchtree<string, MovieData> &bst2)
{
  //Create a struct to store movie information
  struct MovieData movieInfo;
	
  //Reads movies1.txt
  ifstream moviesFile(moviesFilename);
  
  //These variables are used to calculate the average movie rating	
  double sum = 0;
  double average = 0; 
  
  //Checks for file Error
  if (!moviesFile.good()){

    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }


  moviesFile >> movieInfo.id;  // get first ID, or set EOF flag if file empty:
  
  while (!moviesFile.eof()){

    // we have more data, so input publication year and movie name:
    moviesFile >> movieInfo.pubYear;
    
    getline(moviesFile, movieInfo.name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    movieInfo.name = trim(movieInfo.name);  
   
	//We send the information we currently have of the movie and pass it to
	//getReviews in order to store all the ratings of the current movie id 
	getReviews(reviewsFilename, movieInfo);
    
	movieInfo.avgRating = 0;
	
	//Calculate the sum of all the ratings   
	sum = movieInfo.Num1Stars + movieInfo.Num2Stars + movieInfo.Num3Stars + movieInfo.Num4Stars + movieInfo.Num5Stars;
  	
	//If the sum is not zero then we calculate the average rating of the movie
	if(sum != 0){
	average = (movieInfo.Num1Stars * 1) + (movieInfo.Num2Stars * 2) + (movieInfo.Num3Stars * 3) + (movieInfo.Num4Stars * 4) + (movieInfo.Num5Stars * 5);  
	  
	movieInfo.avgRating = average / sum;
        }
	else{
	movieInfo.avgRating = 0; //If sum is zero then average rating is zero
	} 
	  
	//When we have finally stored all the movie information we send it to our BST. 
	//bst1 will store the movie id as its key and bst2 will store the movie name as its key
	bst1.insert(movieInfo.id, movieInfo);
	bst2.insert(movieInfo.name, movieInfo);

    //Read the next movie ID from the file
    moviesFile >> movieInfo.id;  // get next ID, or set EOF flag if no more data:
  }
	
	
}


// main
int main()
{
  //Create 2 BST. One for id integer search and the other for name string search
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

  //Function will store all the individual movie information into the BST trees
  //by reading both text files
  InputMovies(reviewsFilename, moviesFilename, bst1, bst2);
	
	//Varibales used to store values of reviews1.txt file
	int x;
	int y;
	int z;
	int w = 0;

	//In order to calculate the amount of reviews we have to read through the reviews file
	//we then add one to varibale 'w' each time the while loop cycles (represents one line in the text file) 
	ifstream reviewsFiles(reviewsFilename);
	reviewsFiles >> x;

	while(!reviewsFiles.eof()){

		reviewsFiles >> y;
		
		reviewsFiles >> z;
		
		w++;
		
		reviewsFiles >> x;
	}
	
	//Displays the number of movies and the number of reviews
	cout << "Num movies: " << bst1.size() << endl;
	cout << "Num reviews: " << w << endl;
	
	cout << endl;
	
	//Displays the size and height of both Binary Search Trees that were created
	//to store movie information
	cout << "Tree by movie id: " <<  "size=" << bst1.size() << ", "
         << "height=" << bst1.height() << endl;
	cout << "Tree by movie name: " <<  "size=" << bst2.size() << ", "
         << "height=" << bst2.height() << endl;
	cout << endl;

	//Used to detertime if the movie name contains all intgers or mix intgers and characters
	int token;
        int token2;
	
	//Variables used to store the User input based on int Id or string name
  	string user;
  	int movId;
	
	//Asks user for an input. First being stored as a string value.
  	cout << "Enter a movie id or name (or # to quit)> ";
  	getline(cin, user);

	//Gets the string length of the user input 
	int length = user.length();
  	
  //Loop that terminates if the user inputs '#'	
  while(user != "#"){
	
	//First token is to count the number of alphabetic characters in the string
	//Second token is to count the number of non-alphabetic characters in the string 
	token = 0;
	token2 = 0;
	
	//Creates a pointer struct 
	struct MovieData *ptr;

	//Loop traverses through the entire string length
	for(int i = 0; i < length; i++){

		//If the string has an alphabetic character the token one is increased by one	
		if(isalpha(user[i]) != 0){

			token++;
		}
		//If the string has non-alphabetic characters then the token is increased by one	
		if(isalpha(user[i]) == 0 && user[i] != ' '){

			token2++;
		}
	
	
         }  
	  
	//If the number of alpha characters found in the user string are equal to the length of the string then the user input is a movie name
	//If the amount of alpha characters found in the user string are less than the lenght of the string then the user input is a movie name
	if(token != length || token == length){

		//The pointer struct now points to what is returned from bst2 by the BST function 'search'. The movie name is used as a key 
		ptr = bst2.search(user);	
	}
	//If the number of non-alpha characters found in the user string are equal to the lenght then the user input is a movie numerical ID         
	if(token2 == length){

		//If the user input is not a string then it means it is a intger movie id
	        //Thus we convert the string to an intger using 'stoi'
		movId = std::stoi(user);


		//The BST search function is used and the movie id is now passed as the key
	        //The pointer struct now points at the value returned from bst1
		ptr = bst1.search(movId);
	}
	 
	//If the pointer has a value of null then the movie was not found  
	if(ptr == nullptr){

		cout << "not found..." << endl;
		cout << endl;
		cout << "Enter a movie id or name (or # to quit)> ";
                
		getline(cin, user);
		length = user.length(); //New Lenght of string is stored
		
		continue;
	}
	
	//If the value is not returned as null then we can display the values of the struct that corresponds 
	//To the movie being search for. The pointer struct is then used to display each value in the struct it points at
        cout << "Movie ID: " << ptr->id << endl;  
	cout << "Movie Name: " << ptr->name << endl;
	cout << "Avg rating: " << ptr->avgRating << endl;
	cout << "5 stars: " << ptr->Num5Stars << endl;
	cout << "4 stars: " << ptr->Num4Stars << endl;
	cout << "3 stars: " << ptr->Num3Stars << endl;
	cout << "2 stars: " << ptr->Num2Stars << endl;
	cout << "1 star: " << ptr->Num1Stars << endl;
	cout << endl;  
	  
	cout << "Enter a movie id or name (or # to quit)> ";
        getline(cin, user);
	length = user.length(); 
  }
	
  
 
	
  return 0;
}

