/*test.cpp*/
//
// Lab week 09 / project #04
// 
// // <<Manuel M Martinez>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Lab week 09 / project #04
// 
// Testing for util.cpp?
//

#include <iostream>
#include <vector>

#include "avl.h"
#include "util.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) ???") 
{
	//EchoData("students", 82, 5);
	
	vector<streamoff> matches = LinearSearch("students", 82, 5, "kim", 3);
	
	cout << matches.size() << endl;
}
