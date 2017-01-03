#include<iostream>
#include<fstream>
#include"BinaryHeap.h"
#include"BinaryTree.h"

using namespace std;

class StupidClass
{
  public:
  BinaryTree<StupidClass> *p;
  char ltr;
  int c;
  BinaryTree<char> obj;
  bool operator <(const StupidClass &rhs) const
  {

    return c < rhs.c;
  }
  void setLetter(char l)
  {
    ltr = l;
  }  
  void setCount(int ct)
  {
    c = ct;
  }
  char getLetter() const
  {
    return ltr;
  }
  int getCount() const
  {
    return c;
  }
};

class OPover
{
  public:
  BinaryTree<StupidClass> *p;
  OPover()
  {
    p = NULL;
  }
  OPover(BinaryTree<StupidClass> *b)
  {
    p = b;
  }
  bool operator <(const OPover &rhs) const
  {
    return *p < *(rhs.p);
  }
  BinaryTree<StupidClass> * ReturnP()
  {
    return p;
  }  
};

int main(int argc, char **argv) 
{
// general variables
int counts[256] = {};
int countsize = 0;
StupidClass obj, node;
OPover ptr;
BinaryTree<StupidClass> * objptr;
BinaryTree<StupidClass> * ptarray[256]= {};
//BinaryTree<StupidClass> * min1;
//StupidClass obarray[256] ={};
OPover minobj1, minobj2;
//BinaryTree<StupidClass> * min2;
int binary[256] = {};

// read in characters
char c;
ifstream inf(argv[1]);

  while (inf.get(c))
  {
    for (int i=0; i<256; i++)
    {
      if ( c == i ) 
        counts[i]++; 
    }
  }

  

  for(int j=0; j < 256; j++)
  {
    ptarray[0] = NULL;
  }

  for(int v=0; v < 256; v++)
  {
    if(counts[v] != 0)
      countsize++;
  }
int counter5 = 0;
StupidClass obarray[countsize];
  for(int g=0; g < 256; g++) // make array of StupidClass objects from txt
  {
    if(counts[g] != 0)
    { 
      obj.setLetter((char) g);
      obj.setCount(counts[g]);
      //cout << "letter " << obj.getLetter() << " count " << obj.getCount() << endl; 
      obarray[counter5] = obj;
      counter5++;
    }
  }

/*  for(int k=0; k< countsize; k++)
  {
    cout << obarray[k].getLetter() << " " << obarray[k].getCount() << endl;
  }
*/
int caution = 0;
  for(int z = 0; z < 256; z++) //make array of pointers to BinaryTree objects
  {
    if(obarray[z].getCount() !=0)
    {
    //cout << "letter " << obarray[z].getLetter() << " count " << obarray[z].getCount() << endl;
 
    objptr = new BinaryTree<StupidClass> (obarray[z] , NULL, NULL);
    ptarray[caution] = objptr;
    caution++;
    //cout << ptarray[0]->getobCount().getCount() << endl;
    }
  }
 // cout << "put into heap" << countsize << endl;

  BinaryHeap< OPover > btreeptrs(256); 
  
  for (int i=0; i< countsize; i++)
  {
    if(obarray[i].getCount() == 0) break;
      //objptr = new BinaryTree<StupidClass> (obarray[i], NULL, NULL);
      btreeptrs.insert(OPover(ptarray[i])); // probably made a binary heap
  } 
  while(!btreeptrs.isEmpty())
  {
    btreeptrs.deleteMin(minobj1);
    if(btreeptrs.isEmpty()) break;
    btreeptrs.deleteMin(minobj2);
    node.setLetter((char)0);
    node.setCount(minobj1.ReturnP()->getobCount().getCount() + minobj2.ReturnP()->getobCount().getCount());
    objptr = new BinaryTree<StupidClass>(node, minobj1.ReturnP(), minobj2.ReturnP()); 
    //cout << minobj1.ReturnP()->getobCount().getCount() << " " << minobj2.ReturnP()->getobCount().getCount() << endl;
    btreeptrs.insert(OPover(objptr));
  }
int zero = 0;
(minobj1.ReturnP())->printTree(binary,zero);

}



