/*avl.h*/

//
// AVL tree: this code DOES NOT rebalance.  Right now the heights are updated after
// an insert, but that's it.  Instead, a public "rotate" function is provided that
// lets you call the _RightRotate and _LeftRotate functions in order to test them.
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

  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
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

  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //
  void _copytree(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      //
      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
    }
  }
  
  void _RotateToFix(NODE* Parent, NODE* N, TKey key)
  {
	  //Makes sure node N is not NULL
	  assert(N != nullptr);
	  
	 int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
     int hR = (N->Right == nullptr) ? -1 : N->Right->Height;
  
	  //Makes sure the height difference is greater than 1/-1 and not = to 0
	  assert(std::abs(hL - hR) > 1);
	  
	  //Calculates height difference
	  int heightD = hL - hR; 
	  
	  if(heightD > 1)//Case 1 or Case 2
	  {
		  if(key < N->Left->Key)//Case 1 
		  {
			  _RightRotate(Parent, N);
		  }
		  else//Case 2 
		  {
		      _LeftRotate(N, N->Left);
			  _RightRotate(Parent, N);
		  }
	  
	  }
	  else
	  {
		  if(key < N->Right->Key)//Case 3
		  {
			 _RightRotate(N, N->Right);
			 _LeftRotate(Parent, N);
			  
		  }
		  else//Case 4
		  {
			  _LeftRotate(Parent, N);
		  }
	  }
  
  
  }
  //
  // _RightRotate
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.  You'll need to take all this into account when linking in the
  // new root after the rotation.  Don't forget to update the heights as well.
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    NODE* L = N->Left;
    NODE* B = L->Right;
    
    N->Left = B;
    L->Right = N;
    
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
   
   //Update Heights
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
   
   newH = 1 + max(HL, HR);
   N->Height = newH;
   
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
   
   newH = 1 + max(HL, HR);
   L->Height = newH;
   
   
    
  }

  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);
    
    NODE* L = N->Right;
    NODE* B = L->Left;
    
    N->Right = B;
    L->Left = N;
    
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
   
   //Update Heights
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
   
   newH = 1 + max(HL, HR);
   N->Height = newH;
   
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
   
   newH = 1 + max(HL, HR);
   L->Height = newH;

  }

  //Private destructor
  void _destroy(NODE* current)
  {
	  if(current)
	  {
	  _destroy(current->Left);
	  _destroy(current->Right);
	  delete current;
	  }
  
  }

  int _distance(TKey key)
  {
	int count = 0; 
    NODE* cur = Root;
    
	while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return count;
      }

      if (key < cur->Key)  // search left:
      {
		count++;
        cur = cur->Left;
      }
      else
      {
		count++;
        cur = cur->Right;
      }
    }//while  

    // if get here, not found
    return -1;
  }


public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  avltree(avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }

  //Destructor
  virtual ~avltree()
  {
      NODE* current = Root;
	 _destroy(current);
    
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  //
  // height
  //
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
      }

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

  //
  // insert
  //
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;
	

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)// already in tree
		{  
        return;
		}
		
      nodes.push(cur);  // stack so we can return later:

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
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
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
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    // 
    // 4. update size:
    //
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodes.empty())
    {
      cur = nodes.top();
      nodes.pop();
	  
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
	  
      
	  int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;
    }//while

    //
    // done!
    //
    return;
  }
  
  //Clear function calls private destructor
  void clear()
  {
      
	  NODE* cure = Root;
     _destroy(cure);
    
	// Re-initialize root pointer and size to "empty":
    Root = nullptr;
    Size = 0;
    
    
  }

  //Finds the distance between two keys 
  int distance(TKey k1, TKey k2)
  {
	int k1H = 0;
	int k2H = 0;
	int kH = 0;
	
	//When their in the same branch
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
	//If they are in opposite branches
	else if((k1 < Root->Key && k2 > Root->Key) || (k1 > Root->Key && k2 < Root->Key))
	{
		k1H = _distance(k1);
		k2H = _distance(k2);
		
	}
	//Same side but to the left
	else if(k1 < Root->Key && k2 < Root->Key)
	{
		
		curr = curr->Left;
		
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
			else
			{
				k3 = curr->Key;
				break;
			}
			
		}
		
		k1H = _distance(k1);
		k2H = _distance(k2);
		k3H = _distance(k3);
		
		k1H = k1H - k3H;
		k2H = k2H - k3H;
		
	}
	//Same side but to the right
	else if(k1 > Root->Key && k2 > Root->Key)
	{
		curr = curr->Right;
		
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
			else
			{
				k3 = curr->Key;
				break;
			}
			
		}
			
		k1H = _distance(k1);
		k2H = _distance(k2);
		k3H = _distance(k3);
		
		k1H = k1H - k3H;
		k2H = k2H - k3H;
	}
	
	//Checks if one Key was not found in the tree
	if(kH != -1)
	{
		kH = k1H + k2H;
	}
	
	return kH;
	
}

  // inorder:
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  void inorder()
  {
    cout << "Inorder: ";

    _inorder(Root);

    cout << endl;
  }

  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }

  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }

  //
  // rotate:
  //
  // The idea of this function is to rotate the tree anywhere you want,
  // for testing purposes.  The heights are not checked, and the AVL
  // condition is ignored.  If you call to rotate the tree around the
  // key 123, the tree is rotated.
  //
  // Pass 1 to RIGHT rotate at key, pass 4 to LEFT rotate at key.
  // The function walks down the tree to find key, performs the rotation,
  // and then walks up the tree fixing the heights.  The rotations are 
  // performed by the helper functions _RightRotate and _LeftRotate.  If
  // those functions are working correctly, the tree will be rotated 
  // properly and all heights will be correct.
  //
  // Returns true if the rotation was performed, false if not (e.g. if
  // the key cannot be found).
  //
  // **NOTE**  This function is for testing purposes only, it should
  // be removed from the final AVL class.
  //
  bool rotate(int rotation, TKey key)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to find N:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // found!
        break;

      nodes.push(cur);  // stack so we can return later:

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
    // if we didn't find N, return --- there's nothing to do
    //
    if (cur == nullptr)
      return false;

    //
    // we have found N, perform the rotation:
    //
    if (rotation == 1)
    {
      _RightRotate(prev, cur);
    }
    else if (rotation == 4)
    {
      _LeftRotate(prev, cur);
    }
    else  // invalid parameter:
      return false;

    //
    // now walk up tree and fix heights:
    //
    while (!nodes.empty())
    {
      cur = nodes.top();
      nodes.pop();

      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
      int hCur = 1 + std::max(hL, hR);

      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;
    }//while

    // done:
    return true;
  }

};
