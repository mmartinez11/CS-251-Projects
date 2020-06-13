//This file contains the code for my Binary Search Tree. This BST will serve as a tool to store important information such as movie name, ID, and the amount of reviews it recieved in each category.
//This tree is able to store a key and also a struct that has stored all the information that we need about each individual movie. In addition the tree has private and public functions
//that allow it to share information with the user upon being called. Information such as the height, size, and the information stored in each individual struct. Although not all functions
//will be used in this specific project it is still helpfull to have them in the scenario that the program is modified for other purposes. In addition they are useful for debugging.  
//CS 251 Project 2 UIC <Manuel M Martinez> 

#pragma once

#include <iostream>
#include <algorithm>

using namespace std;
 
//Template is updated to include Key and Value 
template<typename TKey, typename TValue>
class binarysearchtree{

private:
  struct NODE{

    TKey  Key;
    TValue Value;
    NODE* Left;
    NODE* Right;
  };
  

  NODE* Root;
  int   Size; 
  
  //Recursive private function that traverses the BST and returns the height of the tree 
  int _height(NODE* cur)
  {
    if (cur == nullptr)
      return -1;
    else
    {
      int heightL = _height(cur->Left);
      int heightR = _height(cur->Right);

      return 1 + std::max(heightL, heightR);
    }
  }

//Recursive private copy constructor. Its job is to traverse the orginal BST and store its 
//Keys and Values into the copy BST.    
void _copy(NODE* cur){

    //Checks for null current 
    if (cur == nullptr){
      return;
	  }

    else{
	
      //Inserts the root values of the original BST into the 
      //root values of the copy BST first. Then it begins to traverse 
      insert(cur->Key, cur->Value);
      _copy(cur->Left);
      _copy(cur->Right);
    }
  
  
  }
  
  //Recursive function used to return the key values of the BST in ascending order.
  //Traverses the BST left to right.
  void _inorder(NODE* cur){

    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << cur->Key << " ";
      _inorder(cur->Right);
    }
  }
  
  //Recursive private destructor. When it is called it deletes all the nodes in 
  //the BST.
  void _destroy(NODE* current){

	  if(current){

	  _destroy(current->Left);
	  _destroy(current->Right);
	  delete current;
	  }
  }
  
  public:
   
  //Default constructor. Creates a BST by making a Root pointer.
  binarysearchtree(){

    Root = nullptr;
    Size = 0;
  }
  
  //Copy constructor: Calls Private Recursive Private constructor
  //Creates a Root pointer for the copy BST
  binarysearchtree(const binarysearchtree& other){

	  Root = nullptr;
	  Size = 0;
	  
	  _copy(other.Root);
  }

  //Destructor: Calls a private destructor recursive function.
  //Passes a pointer pointing to the Root of the BST 
  virtual ~binarysearchtree(){

      NODE* current = Root;
	 _destroy(current);
    
  }
  
  //Function that returns the Size of the BST
  int size(){

    return Size;
  }
  
  //Function that returns the height of the BST by calling a 
  //Private recursive function.
  int height(){

    return _height(Root);
  }
  
  //Function is used to search the BST for a specific Key. The function 
  //traverses the BST checking every node for the Key and returns the respective value.   
  TValue* search(TKey key){

    NODE* cur = Root;

    while (cur != nullptr){

      if (key == cur->Key){ // Already in the tree
        
	return &(cur->Value);
      }
      if (key < cur->Key){  //Search to the left
      
        cur = cur->Left;
      }
      else{

        cur = cur->Right;
      }
    } 

    //Not found
    return nullptr;
  }
  
  //Function is used to insert the Key and Value into a new node in the BST
  void insert(TKey key, TValue value){

    NODE* prev = nullptr;
    NODE* cur = Root;

   
    //Searches to see if tree already contains a key
    while (cur != nullptr){

      if (key == cur->Key){ //Found in tree
        return;
	}

      if (key < cur->Key){ //Searches left
     
        prev = cur;
        cur = cur->Left;
      }
      else{

        prev = cur;
        cur = cur->Right;
      }
    }

    //Key is not in tree, so it allocates
    //a brand new node to insert with the Key and Value
    NODE* newNode;
    newNode = new NODE();
    
    newNode->Key = key;
    newNode->Value = value;
    
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //Links the new node using cur as null
    //prev is used to show were we fell out of the tree.  
    //if prev is null, then the tree is empty and the Root pointer needs to be updated.
    if (prev == nullptr){

      	Root = newNode;
	}
    else if (key < prev->Key){

      	prev->Left = newNode;
	}
    else{

      	prev->Right = newNode;
	}
  
    //Updates size
    Size++;
  }
  
  //Function that returns the key values of the BST
  //Calls a private recursive function 
  void inorder(){

    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }
  
   //Function that clears the BST. 
   //Calls a private recursive destructor
   void clear(){
      
    NODE* cure = Root;
     _destroy(cure);

    // Re-initializes root pointer and size to "empty"
    Root = nullptr;
    Size = 0;
    
    
  }

};




  
