#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class BinaryTree
{
  T object;
  BinaryTree<T> *left;
  BinaryTree<T> *right;

public:
  BinaryTree();
  bool operator< (const BinaryTree <T> &rhs)const;
  BinaryTree(T &obj, BinaryTree<T> *lptr, BinaryTree<T> *rptr);
  void printTree(int binary[], int start);
  const T& getobCount() const;  
  void setObject(T obj);
  void setLeft(BinaryTree<T> *l);
  void setRight(BinaryTree<T> *r);
};


template <class T>
BinaryTree<T>::BinaryTree() 
{
} 

template <class T>
BinaryTree<T>::BinaryTree(T &obj , BinaryTree<T> *lptr, BinaryTree<T> *rptr)
{
  setObject(obj);
  setLeft(lptr);
  setRight(rptr);  
} 

template <class T>
void BinaryTree<T>::setObject(T obj)
{
  object = obj;
}

template <class T>
void BinaryTree<T>::setLeft(BinaryTree<T> *l)
{
  left = l;
}


template <class T>
void BinaryTree<T>::setRight(BinaryTree<T> *r)
{
  right = r;
}

template <class T>
bool BinaryTree<T>::operator< (const BinaryTree <T> &rhs)const
{
  bool temp = (object < rhs.object);   
  return temp;// (*object < *(rhs.object));
} // operator<

template <class T>
const T& BinaryTree<T>::getobCount() const
{
  return object;
}

template <class T>
void BinaryTree<T>::printTree(int binary[], int start)
{
  //cout << "start " << start << endl;
  if(left)
  {
    binary[start] = 0;
    //cout << "left " << left->getobCount().getCount() << endl;
    left->printTree(binary, start+1);
  }

  if(right)
  {
    binary[start] = 1;
   // cout << "right " << right->getobCount().getCount() << endl;
 
    right->printTree(binary, start+1);
  }
  
  if(!left && !right)
  {
    cout << object.getLetter() << setw(5) << object.getCount() << ' ';
    for(int i = 0; i < start; i++)
      cout << binary[i];
    cout << endl;
  }
} // printTree()


