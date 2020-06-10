/*test.cpp*/

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) empty tree") 
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(2) AVL tree with 7 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(46, -8);
  avl.insert(29, -3);
  avl.insert(76, -10);
  avl.insert(17, -1);
  avl.insert(50, -6);
  avl.insert(31, -4);	
  avl.insert(100, -7);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 7);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 17);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 29);
  REQUIRE(heights[1] == 1);

  REQUIRE(keys[2] == 31);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 46);
  REQUIRE(heights[3] == 2);
	
  REQUIRE(keys[4] == 50);
  REQUIRE(heights[4] == 0);
 
  REQUIRE(keys[5] == 76);
  REQUIRE(heights[5] == 1);
	
  REQUIRE(keys[6] == 100);
  REQUIRE(heights[6] == 0);
	

}


TEST_CASE("(3) AVL tree with 3 nodes") 
{
  avltree<int, int>  avl;

  // build a simple BST tree with 3 nodes:
  avl.insert(46, -8);
  avl.insert(29, -3);
  avl.insert(76, -10);
  


  // Tests:
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  REQUIRE(keys[0] == 29);
  REQUIRE(heights[0] == 0);
	
  REQUIRE(keys[1] == 46);
  REQUIRE(heights[1] == 1);
  
  REQUIRE(keys[2] == 76);
  REQUIRE(heights[2] == 0);

}

TEST_CASE("(4) AVL tree with 1 nodes") 
{
  avltree<int, int>  avl;

  // build a simple BST tree with 3 nodes:
  avl.insert(46, -8);
  


  // Tests:
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);

  REQUIRE(keys[0] == 46);
  REQUIRE(heights[0] == 0);
	


}

TEST_CASE("(4) AVL tree with Left Rotation") 
{
  avltree<int, int>  avl;

  // build a simple BST tree with 3 nodes:
  avl.insert(1, -8);
  avl.insert(2, -8);
  avl.insert(3, -8);


  // Tests:
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  REQUIRE(keys[0] == 1);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 2);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 3);
  REQUIRE(heights[2] == 0);
	


}

TEST_CASE("(4) AVL tree with Right Rotation") 
{
  avltree<int, int>  avl;

  // build a simple BST tree with 3 nodes:
  avl.insert(3, -8);
  avl.insert(2, -8);
  avl.insert(1, -8);


  // Tests:
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  REQUIRE(keys[0] == 1);
  REQUIRE(heights[0] == 0);
	
	REQUIRE(keys[1] == 2);
  REQUIRE(heights[1] == 1);
	
	REQUIRE(keys[2] == 3);
  REQUIRE(heights[2] == 0);
	


}