// CS 251 Project 1 UIC <Manuel M Martinez> 
// Project #01: input movie review data from a file, and output moviename, # of 
// reviews, average review, and # of reviews per star.
//
// File example "movie1.txt":
//   Finding Nemo
//   5
//   4
//   5
//   4
//   5
//   -1
//
// Output:
//  Movie: Finding Nemo
//  Num reviews: 5
//  Avg review:  4.6
//  5 stars: 3
//  4 stars: 2
//  3 stars: 0
//  2 stars: 0
//  1 star:  0
//

#include <iostream>
#include <fstream>
#include <string>

#include "myvector.h"

using namespace std;

// functions from student.cpp:
myvector<int> InputData(string filename, string& moviename);
double   GetAverage(myvector<int> reviews);
myvector<int> GetNumStars(myvector<int> reviews);

int main()
{
  myvector<int>  reviews;
  myvector<int>  numstars;
  double    avg;
  string    filename, moviename;

  //
  // 1. input filename and then the review data:
  //
  cin >> filename;

  reviews = InputData(filename, moviename);

  cout << "Movie: " << moviename << endl;
  cout << "Num reviews: " << reviews.size() << endl;

  //
  // 2. average review
  //
  avg = GetAverage(reviews);
  cout << "Avg review:  " << avg << endl;

  //
  // 3. # of 5 stars, 4 stars, etc
  //
  numstars = GetNumStars(reviews);

  for (int i = numstars.size(); i > 0; --i)  
  {
    //
    // i is 5, 4, 3, 2, 1:
    //
    if (i == 1)
      cout << i << " star:  " << numstars.at(i - 1) << endl;
    else
      cout << i << " stars: " << numstars.at(i - 1) << endl;
  }

  return 0;
}
