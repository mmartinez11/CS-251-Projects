//This is a fully functional AVL tree. This tree will rotate and balance when a new key is inserted
//into the tree. 
//CS 251 Project 3 UIC <Manuel M Martinez>  

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

  // _inorder does the actual inorder traversal and output 
  // to console. It displays the Keys, Values, and Heights.
  void _inorder(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder(cur->Left);
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }

  //Does an inorder traversal to store the keys, of the nodes in the tree, into a stack so they can
  //be output by the console. 
  void _inorder_keys(NODE* cur, std::vector<TKey>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_keys(cur->Left, V);
      V.push_back(cur->Key);
      _inorder_keys(cur->Right, V);
    }
  }
  
  //Does an inorder traversal to store the values, of the nodes in the tree, into a stack so they can
  //be output by the console. 
  void _inorder_values(NODE* cur, std::vector<TValue>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_values(cur->Left, V);
      V.push_back(cur->Value);
      _inorder_values(cur->Right, V);
    }
  }

  //Does an inorder traversal to store the heights, of the nodes in the tree, into a stack so they can
  //be output by the console. 
  void _inorder_heights(NODE* cur, std::vector<int>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_heights(cur->Left, V);
      V.push_back(cur->Height);
      _inorder_heights(cur->Right, V);
    }
  }

  // Given a tree, inserts the (key, value) pairs into the copy tree.
  void _copytree(NODE* cur)
  {
    if (cur == nullptr)
    {
      return;
    }
    else
    {
     
      //To copy the tree every node from the original tree must be properly 
      //inserted to the copy tree 
      insert(cur->Key, cur->Value);

     //Traverse the tree from Left to Right 
      _copytree(cur->Left);
      _copytree(cur->Right);
    }
  }
  
  //This function is called when the AVL tree is broken at node 'N'
  void _RotateToFix(NODE* Parent, NODE* N, TKey key)
  {
	  //Makes sure node N is not NULL
	  assert(N != nullptr);
	  
	 //Stores the heights of the Left and Right Node of N
	 int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
         int hR = (N->Right == nullptr) ? -1 : N->Right->Height;
  
	  //Makes sure the height difference is greater than 1/-1 and not = to 0
	  assert(std::abs(hL - hR) > 1);
	  
	  //Calculates the height difference
	  int heightD = hL - hR; 
	  
          //If the height difference is bigger than 1 then
	  //Its Case 1 or Case 2 
	  if(heightD > 1)
	  {
	          //Case 1
    		  if(key < N->Left->Key)
		  {
			  _RightRotate(Parent, N);
		  }
		  //Case 2 
		  else
		  {
		      _LeftRotate(N, N->Left);
			  _RightRotate(Parent, N);
		  }
	  
	  }
	  //Is the height difference is less than -1 then
	  //Its Case 3 or Case 4
	  else
	  {
		  //Case 3
		  if(key < N->Right->Key)
		  {
			 _RightRotate(N, N->Right);
			 _LeftRotate(Parent, N);
			  
		  }
		  //Case 4
		  else
		  {
			  _LeftRotate(Parent, N);
		  }
	  }
  
  }
 
  // Right Rotates the tree around the node N, where Parent is N's parent.
  void _RightRotate(NODE* Parent, NODE* N)
  {
    // pre-conditions: N and L must exist
    assert(N != nullptr);  
    assert(N->Left != nullptr);

    //Assigns pointers L and B 
    NODE* L = N->Left;
    NODE* B = L->Right;
    
    //Makes L the parent Node of N, and N the Parent of B
    N->Left = B;
    L->Right = N;
    
    //If Parent is Null then L will now be the Root of the Tree
    //Else Links the Parent of N to L
    if(Parent == nullptr)
    {
       Root = L;
    }
    else if(L->Key < Parent->Key)
    {
       Parent->Left = L;
    }
    else
    {
       Parent->Right = L;
    }
   
   //Update Height of Node N 
   int HL;
   int HR;
   int newH;
   
   if(N->Left == nullptr)
   {
      HL = -1;
   }
   else
   {
      HL = (N->Left)->Height;
   }
   
   if(N->Right == nullptr)
   {
      HR = -1;
   }
   else
   {
      HR = (N->Right)->Height;
   }
   
   //Calculates the new Height at node N 
   newH = 1 + max(HL, HR);
   N->Height = newH;
   
   //Update the Height of Node L
   if(L->Left == nullptr)
   {
      HL = -1;
   }
   else
   {
      HL = (L->Left)->Height;
   }
   
   if(L->Right == nullptr)
   {
      HR = -1;
   }
   else
   {
      HR = (L->Right)->Height;
   }
   
   //Calculates the new Height at Node L
   newH = 1 + max(HL, HR);
   L->Height = newH;
   
  }

  //Left Rotates the tree around the node N, where Parent is N's parent.
  void _LeftRotate(NODE* Parent, NODE* N)
  {
    // pre-conditions: N and R must exist
    assert(N != nullptr);  
    assert(N->Right != nullptr);
    
    //Assigns pointers L and B
    NODE* L = N->Right;
    NODE* B = L->Left;
    
    //Makes L the parent Node of N, and N the Parent of B
    N->Right = B;
    L->Left = N;
    
    //If Parent is Null then L will now be the Root of the Tree
    //Else Links the Parent of N to L
    if(Parent == nullptr)
    {
       Root = L;
    }
    else if(L->Key < Parent->Key)
    {
       Parent->Left = L;
    }
    else
    {
       Parent->Right = L;
    }
   
   //Update Height of Node N 
   int HL;
   int HR;
   int newH;
   
   if(N->Left == nullptr)
   {
      HL = -1;
   }
   else
   {
      HL = (N->Left)->Height;
   }
   
   if(N->Right == nullptr)
   {
      HR = -1;
   }
   else
   {
      HR = (N->Right)->Height;
   }
   
   //Calculates the new Height at node N 
   newH = 1 + max(HL, HR);
   N->Height = newH;
   
   //Update Height of Node L
   if(L->Left == nullptr)
   {
      HL = -1;
   }
   else
   {
      HL = (L->Left)->Height;
   }
   
   if(L->Right == nullptr)
   {
      HR = -1;
   }
   else
   {
      HR = (L->Right)->Height;
   }
   
   //Calculates the new Height at Node L
   newH = 1 + max(HL, HR);
   L->Height = newH;

  }

  //Recursive Private destructor
  void _destroy(NODE* current)
  {
	  //Execute if Current is not Null 
	  if(current)
	  {
	  _destroy(current->Left);
	  _destroy(current->Right);

          //Deletes Node
	  delete current;
	  }
  
  }

  //Private Helper function searches for a key in the AVL tree
  //Returns the distance of the key from the Root node 
  int _distance(TKey key)
  {
	//'count' (Distance) increased by one each time a node is visited 
	int count = 0; 
        NODE* cur = Root;
    
    //Traverses the Tree searching for the Key until cur is Null 
    while (cur != nullptr)
    {
      //If key is found the count is returned 
      if (key == cur->Key) 
      {
        return count; 
      }
	
      //search Left
      if (key < cur->Key)  
      {
	count++;
        cur = cur->Left;
      }
      //search Right
      else
      {
	count++;
        cur = cur->Right;
      }
    }

    //If we get here, key is not found 
    return -1;
  }


public:

  // default constructor:
  // Creates an empty tree.
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  // copy constructor:
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }

  //AVL Destructor
  virtual ~avltree()
  {
      NODE* current = Root;
      _destroy(current);
    
  }

  // Returns the number of nodes in the tree, 0 if empty.
  int size()
  {
    return Size;
  }

  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not found.
  TValue* search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      //Key found in tree, return pointer
      if (key == cur->Key)  
      {
        return &cur->Value;
      }
      //search to the left
      if (key < cur->Key)  
      {
        cur = cur->Left;
      }
      //search to the right
      else
      {
        cur = cur->Right;
      }
    }

    //If we get here, key was not found
    return nullptr;
  }

  // Insert the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  void insert(TKey key, TValue value)
  {

    NODE* prev = nullptr;
    NODE* cur = Root;

    //Stores Nodes visited into a stack to be used later for updating Heights
    stack<NODE*> nodes;

    //Search to see if tree already contains the key
    while (cur != nullptr)
    {
      //Already in tree
      if (key == cur->Key)
		{  
        return;
		}
		
      //Push Node visited into stack
      nodes.push(cur);

      // search to the Left
      if (key < cur->Key) 
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }
 
    //If key is not found in the tree then we allocate
    //a new node to insert 
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Height = 0;  //Starting Height of 0
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //Link the new node using pointer prev 
    //If prev is null then newNode will be the root of the tree
    if (prev == nullptr)
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;
 
    //update size
    Size++;

    //Walk back up tree using the node stack and update heights were needed
    //Fix tree at a Node where AVL is broken
    while (!nodes.empty())
    {
      cur = nodes.top();
      nodes.pop();
	  
	  //If Node stack is empty then assign NULL to prev
	  if(nodes.empty())
	  {
	     prev = nullptr;
	  }
	  else
	  {
	      prev = nodes.top();
	  }
	
      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
	  
	  //Checks the differences in heights
	  int checkH = hL - hR;
	  
		  //If the difference is not one of 3 values then its broken at 'cur'
		  if(checkH != 1 && checkH != 0 && checkH != -1)
		  {
			  //Will rotate to fix at that point 
			 _RotateToFix(prev, cur, key);
			  continue;
		  }
	  
      	  //Calculate the Height of the current Node
	  int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur) //Height didn't change, so no need to go further
        break;
      else  //Height changed, update and keep going
        cur->Height = hCur;
    }

    return;
  }
  
  //Clear function calls private destructor to clear tree
  void clear()
  {
      
     NODE* cure = Root;
     _destroy(cure);
    
    //Re-initialize root pointer and size to "empty":
    Root = nullptr;
    Size = 0;
    
  }

  //Finds the distance between two keys, using helper function _distance 
  int distance(TKey k1, TKey k2)
  {
	//Values used to calculate the distance between two keys
	int k1H = 0;
	int k2H = 0;
	int kH = 0;
	
	//Values used when keys are in the same branch (Left/Right of root)
	TKey k3;
	int k3H = 0;	
	NODE* curr = Root;
	
	//If one of the keys does not exist 
	if(_distance(k1) == -1 || _distance(k2) == -1)
	{
		kH = -1;
	}
	//If the Keys are the same
	else if(k1 == k2)
	{
		k1H = 0;
		k2H = 0;
	}
	//If One key is the Root
	else if(k1 == Root->Key || k2 == Root->Key)
	{
		if(k1 == Root->Key)
		{
			k1H = _distance(k2);
		}
		else
		{
			k2H = _distance(k1);
		}
		
	}
	//If keys are in opposite branches
	else if((k1 < Root->Key && k2 > Root->Key) || (k1 > Root->Key && k2 < Root->Key))
	{
		k1H = _distance(k1);
		k2H = _distance(k2);
		
	}
	//Keys in the same branch but to the left of the Root
	else if(k1 < Root->Key && k2 < Root->Key)
	{
		
		curr = curr->Left;
		
		//The purpose of this loop is to find were is the last common node between the keys before splitting
		//to a different direction
		while(curr != nullptr)
		{
			
			if(k1 < curr->Key && k2 < curr->Key)
			{
				curr = curr->Left;
				continue;
			}
			else if(k1 > curr->Key && k2 > curr->Key)
			{
				curr = curr->Right;
				continue;
			}
			//When splitting occurs the last common node is assigned to pointer k3
			else
			{
				k3 = curr->Key;
				break;
			}
			
		}
		
		//The distance of each key from the root is computed 
		k1H = _distance(k1);
		k2H = _distance(k2);
		k3H = _distance(k3);
		
		//The distances of key 1 and 2 are subtracted by the distance of their last common node (k3) 
		k1H = k1H - k3H;
		k2H = k2H - k3H;
		
	}
	//Same side but to the right
	else if(k1 > Root->Key && k2 > Root->Key)
	{
		curr = curr->Right;
		
                //The purpose of this loop is to find were is the last common node between the keys before splitting
		//to a different direction
		while(curr != nullptr)
		{
			
			if(k1 < curr->Key && k2 < curr->Key)
			{
				curr = curr->Left;
				continue;
			}
			else if(k1 > curr->Key && k2 > curr->Key)
			{
				curr = curr->Right;
				continue;
			}
                        //When splitting occurs the last common node is assigned to pointer k3
			else
			{
				k3 = curr->Key;
				break;
			}
			
		}
			
                //The distance of each key from the root is computed
		k1H = _distance(k1);
		k2H = _distance(k2);
		k3H = _distance(k3);
		
                //The distances of key 1 and 2 are subtracted by the distance of their last common node (k3)
		k1H = k1H - k3H;
		k2H = k2H - k3H;
	}
	
	//Checks if one Key was not found in the tree
	if(kH != -1)
	{
	   kH = k1H + k2H;
	}
	
        //Returns the distance between two keys
	return kH;
	
}

  // Performs an inorder traversal of the tree, outputting Keys, Values, and Heights
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }

  // Performs an inorder traversal of the tree, outputting Keys
  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }
   
  // Performs an inorder traversal of the tree, outputting Values
  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

  // Performs an inorder traversal of the tree, outputting Heights
  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }

};
