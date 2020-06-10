/*avl.h*/
//
//
// AVL tree: complete, balancing AVL tree class. AVL Tree allows us to create a balanced tree 
// that will store a key and value pair. In addition to returning the value of a certain key using the search function. 
//
// <<Manuel M Martinez>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
// 


#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
	
	//Private Helper functions
	void _inorder(NODE* cur);
	void _inorder_keys(NODE* cur, std::vector<TKey>& V);
	void _inorder_values(NODE* cur, std::vector<TValue>& V);
	void _inorder_heights(NODE* cur, std::vector<int>& V);
	void _copytree(NODE* cur);
	void _destructor(NODE* cur);
	void _RotateToFix(NODE* Parent, NODE* N);//Fix node that breaks avl standards 
	void _RightRotate(NODE* Parent, NODE* N);//Rotate tree to the right at a Node
	void _LeftRotate(NODE* Parent, NODE* N);//Rotate tree to the left at a Node 

public:
  avltree();//Create empty tree 
  avltree(const avltree& other);//Copy Constructor 
  ~avltree();//Destructor 
  
  avltree& operator=(const avltree& other);

  int size();//Return size of tree
  int height();//Return height of tree 
  
  void clear();//Clear tree
  
  TValue* search(TKey key); //Search and return value of a key 
  void insert(TKey key, TValue value); //Insert a key and value pair into avl tree 
  
  int distance(TKey k1, TKey k2);//Calculate and return the distance between two keys 

  void inorder();//Display Tree Keys, Values, and Heights in order 
  std::vector<TKey> inorder_keys(); //Display Tree keys in order
  std::vector<TValue> inorder_values(); //Display Tree values in order 
  std::vector<int> inorder_heights(); //Display Tree Heights in order 

};
