#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std; 

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
	TValue Value;
    NODE* Left;
    NODE* Right;
  };
  

  NODE* Root;
  int   Size; 
  
  
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
  
  void _copy(NODE* cur)
  {
	  if (cur == nullptr)
	  {
      return;
	  }
    else
    {
	 
	 insert(cur->Key, cur->Value);
      _copy(cur->Left);
      _copy(cur->Right);
    }
  
  
  }
  
  void _inorder(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << cur->Key << " ";
      _inorder(cur->Right);
    }
  }
  
  void _destroy(NODE* current)
  {
	  if(current)
	  {
	  _destroy(current->Left);
	  _destroy(current->Right);
	  delete current;
	  }
  
  }
  
  public:
  
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }
  
  //Copy constructor:
  binarysearchtree(const binarysearchtree& other)
  {
	  Root = nullptr;
	  Size = 0;
	  
	  _copy(other.Root);
  
  
  }
  
  //Destructor 
  virtual ~binarysearchtree()
  {
      NODE* current = Root;
	 _destroy(current);
    
  }
  
  int size()
  {
    return Size;
  }
  
  int height()
  {
    return _height(Root);
  }
  
  
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return &(cur->Value);

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  

    // if get here, not found
    return nullptr;
  }
  
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
	newNode->Value = value;
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
	{
      Root = newNode;
	}
    else if (key < prev->Key)
	{
      prev->Left = newNode;
	}
    else
	{
      prev->Right = newNode;
	}
    // 
    // 4. update size and we're done:
    //
    Size++;
  }
  
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }
  
   void clear()
  {
      
	  NODE* cure = Root;
     _destroy(cure);
    // Re-initialize root pointer and size to "empty":
    //
    Root = nullptr;
    Size = 0;
    
    
  }

};




  