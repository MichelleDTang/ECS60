#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1]) // if value in parameter is greater than the biggest number in array
    last = value;
  else
  {
    last = values[count - 1]; // last is made equal to the biggest number in the array

    for(i = count - 2; i >= 0 && values[i] > value; i--) // shift the values to the right 
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value; // put value in array where it belongs
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
  {
    if (values[i] != 0) 
      cout << values[i] << ' ';
  }
  cout << endl;
 
} // LeafNode::print()


LeafNode* LeafNode::remove(int value)
{   // To be written by students
//cout<< count << endl;
if(parent)
{
  if( (count - 1) >= ((leafSize+1) / 2) ) //removing a number from current leaf doesn't require borrowing/merging
  {
    for(int i=0; i < leafSize; i++)
    {
      //cout << value << " " << values [i] << endl;
      if(values[i] == value)
      {
        for(int j=i; j < leafSize-1; j++)//moves everything to left
          values[j]=values[j+1];
        values[count] = 0;
        count--; 
        if(parent)
          parent->resetMinimum(this);
       break;
      }
    }
  }
  else //look to siblings
  {
    for(int i=0; i < leafSize; i++)
    { 
      if(values[i] == value)
      {
        for(int j=i; j < leafSize-1; j++) //shifts everything to the left from the value deleted
          values[j]=values[j+1];
        values[count] = 0;
        count--;
        if(parent)
          parent->resetMinimum(this);
        break;
      }
    }
    
    if (leftSibling) //left exists
    { 
       if((leftSibling->getCount()-1) >= ((leafSize +1)/ 2)) //removing 1 from left would be greater than or equal to minimum
       {
         //cout << "borrowed from left" << endl;
         for(int i=count; i>0; i--)// shift everything to the right to make space or new min
           values[i] = values[i-1];
         values[0] = leftSibling->getMaximum();
         if (parent)
           parent->resetMinimum(this);
         leftSibling->remove(values[0]);
         count++;
          
       } 

       else if((leftSibling->getCount() + count) <= leafSize) //merging must happen into left
       {
         //cout << "merge with left" << endl;
         for(int z=0; z < count; z++)
         {
           leftSibling->insert(values[z]);
           values[z] = 0;
         }
         if(parent)
           parent->resetMinimum(this);
         count = 0;
         if(rightSibling)
         {
           leftSibling->setRightSibling(rightSibling);
           rightSibling->setLeftSibling(leftSibling);
         }
         return this;
       }
       else // look to right sibling
       {
         if((rightSibling->getCount()-1) >= ((leafSize+1)/2))
         {
           //cout << "borrow from right" << endl;
           values[count]=rightSibling->getMinimum();
           rightSibling->remove(values[count]);
           count++;
           parent->resetMinimum(this); 
         }
         else
         {
           //cout << "merge with right" << endl;
           for(int c=0; c < count; c++)
           {
             rightSibling->insert(values[c]);
             values[c] = 0;
           } 
           if(parent)
             parent->resetMinimum(this);
           count = 0;
           rightSibling->setLeftSibling(leftSibling);
           leftSibling->setRightSibling(rightSibling);
           return this;
         }
       }
    }
    else 
    {
      if((rightSibling->getCount()-1) >= ((leafSize+1)/2)) 
      {
        //cout << "borrow from right" << endl;
        values[count]=rightSibling->getMinimum();
        rightSibling->remove(values[count]);
        count++;
        if (parent) //need to reset minimum for right's parent
          parent->resetMinimum(this);
        
      }

      else //merge this into right 
      {
        //cout << "merge with right" << endl;
        for(int c=0; c < count; c++)
        {
          rightSibling->insert(values[c]); 
          //cout << values[c] << endl;
          values[c] = 0;
        }
        if(parent)
          parent->resetMinimum(this);
        count = 0;
        rightSibling->setLeftSibling(NULL);
        return this;
      }
    }
  }
}  
else //leaf is root
{
    //cout << "root" << endl;
    for(int i=0; i < count; i++)
    {
      //cout << value << " " << values [i] << endl;
      if(values[i] == value)
      {
        for(int j=i; j < count; j++)
          values[j]=values[j+1];
        values[leafSize-1] = 0;
        count--;
        break;
      }
    }

}

  return NULL;  // filler for stub
}  // LeafNode::remove()



LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

