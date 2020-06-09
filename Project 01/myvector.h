/*myvector.h*/

// 
// <Manuel M Martinez>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// 
// Project #01: myvector class that mimics std::vector, but with my own
// implemenation outlined as follows:
//
//Instead of using a method that dealt with the use of dynamically allocated arrays. I instead 
//used a method that utilize Linked List. However by using Linked List there was the reality that 
//the performance of the program in the matter of speed would be affected. Therefore in order to make 
//the program more efficient I decided to implement a series of pointers in the at() constructor.
//This will prevent a loop from having to start at the Head node everytime it is trying to traverse the list
//in order to reach a certain destination (Node). 

#pragma once

#include <iostream>  // print debugging
#include <cstdlib>   // malloc, free

using namespace std;

template<typename T>
class myvector
{
private:
  struct NODE{
     
     T Data;
     struct NODE* Next;
  };
  
  struct NODE* Head;
  struct NODE* Tail;
  int Size;
  
  //Pointer used to point at a desired Node at constructor at()
  //when it is non-consecutive access
  struct NODE* iFinder;
  
  //Pointers used to record the last index used and
  //last Node passed. They are used in constructor at() when 
  //it is consecutive access
  struct NODE* lastNode;
  int lastIndex;
  
  T* A;  

public:
  // default constructor:
  myvector(){
    
    Head = nullptr;
    Tail = nullptr;
    Size = 0;
    
    //Set pointers to a default state for later use 
    lastNode = nullptr;
    lastIndex = -1;
    
   }

  // constructor with initial size:
  myvector(int initial_size){
     
    //Set pointers to a default state for later use 
    lastNode = nullptr;
    lastIndex = -1;
    
    Tail = nullptr;
    Head = nullptr;
    
    int i;
    
    //Set the size of linked list to start at zero(will be incremented by push_back)
    Size = 0;
    
    //Creates a Linked List that is equal in size to the desired initial size.
    //Utilizes the constructor push_back in order to create the list
    for(i = 0; i < initial_size; i++){
     push_back(T{});  
    } 
    
  }

  // copy constructor for parameter passing:
  myvector(const myvector& other)
  {
   
    Head = nullptr;
    Tail = nullptr;
    
    //Creates a brand new link list that is equal in size to the orginal we
    //are going to copy 
    for(int i = 0; i < other.Size; i++)
    {
       push_back(T{});
    }
     //Size of linked list is set to the size of the Linked List we 
     //are trying to copy
     Size = other.Size;
     
     //Creates two pointers. temp2Node will point at the Head Node of the Linked List we
     //are trying to copy
     //temp2Node will point at the Head of the Linked List we have created that will store 
     //the values of the original Linked List 
     struct NODE* temp1Node = Head;
     struct NODE* temp2Node = other.Head;
     
     //Loop traverses through every indiviual Node of both the original and the copy Linked List 
     //and stores the Data from the orginal Linked List into the copy Linked List
     for(int i = 0; i < other.Size; i++){
        
        temp1Node->Data = temp2Node->Data;
        temp1Node = temp1Node->Next;
        temp2Node = temp2Node->Next;
     }
  }

  //Constructor erases the Node at postion i from the Linked List  
  T erase(int i)
  {
     //Pointers used to Point to the current Node(starts at Head), the Node marked for deletion
     //and the Node prior to the current Node.
     struct NODE* currentNode = Head;
     struct NODE* previousNode;
     struct NODE* deleteNode;
     
     //The Data value that is stored inside the Node that will be erased is Stored 
     //into this variable so it can returned  
     T deleteData;
     
     int counter = 0;
     
     //Checks if the Node being erased is the Head Node 
     if(i == 0)
     {
         //Checks if the first Node is the only single Node in the Linked List
         if(currentNode->Next == nullptr)
         {
             Head = nullptr;
             Tail = nullptr;
             
             deleteData = currentNode->Data;
             
             delete currentNode;
             currentNode = nullptr;
             
             Size--;
             
         }
         else { //Deletes Head Node and sets the next Node in the list as the Head Node
             
            deleteNode = currentNode;
            currentNode = currentNode->Next;
            Head = currentNode;
            
            deleteData = deleteNode->Data;      
            
            delete deleteNode;
            deleteNode = nullptr;
            
            Size--;
            
         }
     }
     else{
         
         //Loop traverses the Linked List in order to find the Node that needs to be erased 
         while(counter <= i){
             
             //If the Node is found and it is not the Tail Node then it is deleted 
             if(counter == i && currentNode->Next != nullptr){
                 
                deleteNode = currentNode;
                currentNode = currentNode->Next;
                
                previousNode->Next = currentNode;
                
                deleteData = deleteNode->Data;
                
                delete deleteNode;
                deleteNode = nullptr;
                
                Size--;
                break;
             
             }
             //If the Node is found and it is the Tail Node then that Node is deleted and the 
             //previous Node is set to be the new Tail 
             else if(counter == i && currentNode->Next == nullptr){
                 
                 deleteNode = currentNode;
                 Tail = previousNode;
                 
                 currentNode = nullptr;
                 
                 deleteData = deleteNode->Data;

                 delete deleteNode;
                 deleteNode = nullptr;
                 
                 Size--;
                 break;
                 
             }
                
             previousNode = currentNode;
             currentNode = currentNode->Next;
                    
            counter++;
         }   
     }
        //Returns the Data value of the deleted Node 
        return deleteData;
  }

  //Returns a reference to the element at the Node postion i so the element can be read or written
  T& operator[](int i)
  {
     //Returns the Data Value stored at Node postion i using the at() constructor    
     return at(i);
  }
  
  //Returns the elements in the range of postion i and j
  T* rangeof(int i, int j)
  {
      //Calculates the Size of the array 
      int x = (j - i) + 1; 
      
      //Creates a dynamically allocated array 
      A = new T[x];
      
      int z = 0;
      
      //Loops through every postion between i and j. Using the at() constructor
      //to return to the data value at those specific Nodes and stores them in our dynamically allocated array 
      for(int y = i; y <= j; y++){
          
          A[z] = at(y);
          
          z++;
      }
   
    //Returns the dynamically allocated array with all the data values stored 
    return A;
  }  
    
  //Constructor Returns the size of the Linked List 
  int size()
  {
    
    return Size;
  }
  
  //Constructor used to locate a desired data value at a specific Node 
  T& at(int i){
      
      //Set the pointer to point at the beggining of the List 
      iFinder = Head;
      
      //To keep track of which Node is being checked 
      int counter = 0;
   
      //First two if statments are used to find the desired Node if it is in consecutive access
      //Checks if the desired Node is the first Node in the list 
      if(i == 0){
         
         lastNode = Head;
         lastIndex = 0;
         return Head->Data;
      }
      else if(i == lastIndex + 1){ //Checks if the desired Node is the one after the previous Node checked
      
         lastNode = lastNode->Next;
         lastIndex = lastIndex + 1;
         return lastNode->Data;
      }
      else{ 
         
         //The while loop is utilized to find the desired Node when it in non-consecutive access
         while(iFinder != nullptr){
            
            if(counter == i){
               
               return iFinder->Data;
               break;
            }
            else if(counter != i){
               
               iFinder = iFinder->Next;
               counter++;
            }
         
         }
      }
   
  }
   
  //Constructor used to add a brand new Node to a Linked List    
  void push_back(T value)
  {
      //Creates a new Node to be used and linked to a list 
      struct NODE* newNode = new struct NODE();
      newNode->Data = value;
      newNode->Next = nullptr;
     
      //Checks if the new Node will serve as the Head of Linked List 
      // List empty   
      if (Head == nullptr) {
         
      Head = newNode;
      Tail = newNode;
      Size++;
      
      }
      else{ 
      
      //Links the new Node into the end of the List and sets it as the new Tail
      Tail->Next = newNode;
      Tail = newNode;
      
      Size++;
      }
     
  }

};
