//
// Project #01: input movie review data from a file, and output moviename, # of 
// reviews, average review, and # of reviews per star.
//

#include <iostream>
#include <fstream>
#include <string>

#include "myvector.h"

using namespace std;

//
// InputData
//
// Inputs the movie data from the given file, returning the moviename
// (via the parameter) and the individual reviews (via the returned 
// vector).  The reviews are ratings in the range 1..5.
//
// File format: the first line is the moviename.  The name is followed
// by N > 0 reviews, one per line; each review is a value in the range
// 1-5.  The last review is followed by a sentinel value (0 or negative)
// which is discarded.
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
myvector<int> InputData(string filename, string& moviename)
{
  myvector<int>  V;
  ifstream  file(filename); 
  int       x;

  if (!file.good())
  {
    cout << "**Error: unable to open '" << filename << "'." << endl;
    return V;  // empty vector:
  }

  getline(file, moviename);

  //
  // input and store all reviews until sentinel is 
  // reached (0 or negative):
  //
  file >> x;

  while (x > 0)
  {
    V.push_back(x);

    file >> x;  // next value:
  }

  // done, return vector of reviews:
  return V;
}

//
// GetAverage
//
// Returns the average of the values in the vector; if the vector
// is empty then 0.0 is returned.
//
double GetAverage(myvector<int> V)
{
  double sum = 0.0;
  double avg;

  for (int i = 0; i < V.size(); ++i)
  {
    sum += V.at(i);
  }

  if (V.size() == 0)  // beware of divide-by-0:
    avg = 0.0;
  else
    avg = sum / static_cast<double>(V.size());

  return avg;
}

//
// GetNumStars
//
// Given a vector of reviews --- each review in the range 1-5 --- returns
// a vector of counts denoting the # of reviews of each rating.  In other 
// words, if we think of the reviews as "stars", the function returns a 
// vector of 5 counts in this order:  # of reviews of 1 star, # of reviews of
// 2 stars, ..., # of reviews of 5 stars.
//
// Example: suppose reviews contains the reviews 1, 5, 5, 2, 1, 4, 5.  Then
// the function returns a vector containing 5 counts:  2, 1, 0, 1, 3.
//
myvector<int> GetNumStars(myvector<int> reviews)
{
  myvector<int> numstars(5);  // 1, 2, 3, 4, 5 stars

  // let's make sure all the counts are initialized to 0:
  for (int i = 0; i < numstars.size(); ++i)
  {
    numstars.at(i) = 0;
  }

  //
  // for each review, increase count for that particular star (1-5):
  //
  for (int i = 0; i < reviews.size(); ++i)
  {
    int star = reviews.at(i);  // 1-5:

    numstars.at(star - 1)++;   // index 0-4:
  }

  // return counts:
  return numstars;
}
