#include <iostream>
#include "NetDriver.h"
#include "maxfinder.h"
#include "maxheap.h"
#include <cstring>
//#include "QueueAr.h"
//#include "StackAr.h"
 
using namespace std;
 
 
 
 
class pathflow
{
  public:
  short max;
  bool known;
  int path;
  int vertex;
  bool operator >(const pathflow &rhs) const
  {
    return max > rhs.max;
  }
  void setVisited(bool k)
  {
    known = k;
  }
  bool getVisited()
  {
    return known;
  }
  void setV(int c)
  {
    vertex = c;
  }
  int getV()
  {
    return vertex;
  }
  void setPV(int p)
  {
    path = p;
  }
  int getPV(){return path;}
  void setMax(short m)
  {
    max = m;
  }
  short getMax() {return max;}
};
 
class OPover
{
  public:
  pathflow *p;
  OPover()
  {
    p = NULL;
  }
  OPover(pathflow *b)
  {
    p = b;
  }
  bool operator >(const OPover &rhs) const
  {
    return *p > *(rhs.p);
  }
  pathflow * ReturnP()
  {
    return p;
  }  
};  
 
MaxFinder::MaxFinder(const Computer *computers, int numComputers,
  int numTerminals)
{
    compnum = numComputers;
    start = numTerminals;
        nodes = new Node[compnum+1];
    tab = new Table[compnum+1];
    //bool visited[5000] = false;
    check = false;
    bfs = true;
    int l = 0;
    for(int i=1; i <= compnum; i++)
    {
        //ips[i] = computers[l].address;
        nodes[i].address = computers[l].address;
    myhash.insert(computers[l].address, i);
    //cout << "Node index is: " << i << " and the address is " << nodes[i].address << endl;
        if(i+1 == compnum){sink = i;}
    l++;
    }
    finalFlow = 0;
    sink = numComputers;
 
} // MaxFinder()
 
 
int MaxFinder::calcMaxFlow(Edge *edges, int numEdges)
{

    BinaryHeap< OPover > prims(15000);
//    Queue < pathflow* > q(700000);
//    StackAr< pathflow* > stack(700000);
    pathflow *front;
    const char* temp;
    OPover max;
    int index, indexVal,currentCap;
    const char* Address;
    int hashsrc;
    int hashdest;
 
    for(int k = 0; k < numEdges; k++){
    Address = edges[k].src;
    hashsrc = myhash.getIndex(Address);
    temp = edges[k].dest;
    hashdest = myhash.getIndex(temp);
    //cout << "EDGE FROM " << hashsrc << " to " << hashdest << endl;
 
        if(hashdest > start){
        currentCap = nodes[hashsrc].currentSize;
                //cout << "index value is " << indexVal << endl;
                nodes[hashsrc].dest[currentCap] = hashdest;
                nodes[hashsrc].capacity[currentCap] = edges[k].capacity;
                nodes[hashsrc].currentSize++;
                if(hashsrc > start && hashsrc != compnum){
                index = nodes[hashdest].currentSize;
                    nodes[hashdest].dest[index] = hashsrc;
                    nodes[hashdest].currentSize++;
                    nodes[hashdest].capacity[index] = 0;
                }
 
    	}
       
   
    }
 
 
 
 
/*
    for(int i=1; i < compnum; i++){ //make adjacency list
        for(int k = 0; k < numEdges; k++){
              if(edges[k].src == nodes[i].address){
                    temp = edges[k].dest;
                    for( int i = 1; i <= compnum; i++){
                            if(nodes[i].address == temp)
                            indexVal = i;
                    }
            if(indexVal > start){
                currentCap = nodes[i].currentSize; 
                //cout << "index value is " << indexVal << endl;
                nodes[i].dest[currentCap] = indexVal;
                nodes[i].capacity[currentCap] = edges[k].capacity;
                nodes[i].currentSize++;
                if(i > start && i != compnum){
                    index = nodes[indexVal].currentSize;
                    nodes[indexVal].dest[index] = i;
                    nodes[indexVal].currentSize++;
                    nodes[indexVal].capacity[index] = 0;
                }
                   
                //cout << "working index value " << nodes[i].dest[j] << endl;
                    // nodes[i].dest[j] = edges[k].dest;
 
                //cout << "Source is " << nodes[i].address << "with edge capacity " << nodes[i].capacity[j] << " with destination " << nodes[i].dest[j] << endl;
       
                //cout << "J VALUE IS: " << j << endl;
           
                }
            }
       
        }
    }
*/
    for(int w=0; w < start; w++)// make phony source
    {
    int edge = 0;
        nodes[0].dest[w] = w+1;
    edge = nodes[w+1].capacity[0]; 
    for(int t=0; t < nodes[w+1].currentSize; t++)
    {
        if(edge < nodes[w+1].capacity[t])
            edge = nodes[w+1].capacity[t];
    }  
    nodes[0].capacity[w] = edge;
    //cout << "TERMINAL" << nodes[0].dest[w] << endl;
    //cout << "CAPACITY" << nodes[0].capacity[w] << endl;
    nodes[0].currentSize++;
    }
 
 
    while(bfs){    
    // put in heap first
    for(int c = 0; c< start; c++){
    if(nodes[0].capacity[c] != 0){
            pathflow* objptr = new pathflow;
            objptr->setV(0);
        objptr->setMax(nodes[0].capacity[c]);
            prims.insert(OPover(objptr));
    }
    }
    for(int v = 0; v < compnum; v++){
        if(tab[v].known == 1)
        tab[v].known = 0;
    }
 
    //cout << "prims " << endl;
     while(!prims.isEmpty()){ // prims until a path is made or it's empty
   
        prims.deleteMax(max);
 	if(tab[max.ReturnP()->getV()].known != 1){ 

        //cout << "max " << max.ReturnP()->getV() << "from" << max.ReturnP()->getPV() <<  endl;
 
        tab[max.ReturnP()->getV()].known = 1;
        tab[max.ReturnP()->getV()].dv = max.ReturnP()->getMax();
        tab[max.ReturnP()->getV()].pv = max.ReturnP()->getPV();
 
        //stack.push(max.ReturnP());
 
        //cout << "top of stack " << max.ReturnP()->getV() << " previous " << tab[max.ReturnP()->getV()].pv << " with capacity " << tab[max.ReturnP()->getV()].dv << endl;
 
        //if(stack.top()->getV() == sink){
        if(tab[compnum].known == 1){
            prims.makeEmpty();
            break;
    }
    //cout << " for loop" << endl;
 
    for(int s=0; s< nodes[max.ReturnP()->getV()].currentSize; s++)// inserting into heap
    {
    	if(tab[nodes[max.ReturnP()->getV()].dest[s]].known == 0 && nodes[max.ReturnP()->getV()].capacity[s] > 0){
    	        pathflow* objptr = new pathflow;
    	        objptr->setV(nodes[max.ReturnP()->getV()].dest[s]);
    	        objptr->setMax(nodes[max.ReturnP()->getV()].capacity[s]);
    	        objptr->setPV(max.ReturnP()->getV());
    	    prims.insert(OPover(objptr));
        //cout << "vertex into heap " << objptr->getV() << "with capacity " << objptr->getMax() << endl;
       
    	}
      }
    }
   
    }// while prims
 
    //cout << "prims done " << endl;
    //cout << "sink "<< sink << " vs top of stack " << stack.top()->getV() << endl;
 
    //if(stack.isEmpty())
    if(tab[compnum].known != 1)
    break;
    //if(stack.top()->getV() != sink)
      //break;
/*
    front = stack.topAndPop();
    q.enqueue(front);
    //cout << "enqueue from stack " << front->getV() << " " << front->getPV() << endl;
    pathmin = front->getMax();
    tab[front->getV()].known = 0;
    //cout << " pathmin " <<pathmin << " " << front->getV() << endl;;    
 
    while(!stack.isEmpty()){ //filter through and determine flow of path
    //cout << front->getPV() << "equal? " << stack.top()->getV()<< endl;
    //cout << "stack " << front->getPV() << " " << stack.top()->getV() << endl;
   
        if(front->getPV() == stack.top()->getV()){
 
        if(pathmin > stack.top()->getMax()){
        //cout << pathmin << " vs " << stack.top()->getMax() << " " << stack.top()->getV() << endl;
        pathmin = stack.top()->getMax();
        }
       front = stack.topAndPop();
       q.enqueue(front);
       tab[front->getV()].known = 0;
        }
        else{
            tab[stack.topAndPop()->getV()].known = 0;
        }
    }
*/
 
    previous = tab[compnum].pv;
    pathmin = tab[compnum].dv;
    last = compnum;
    //cout << "before the while" << endl;
    while(tab[previous].known != 0){
      //cout << "begin while "<<endl;
          if(pathmin > tab[previous].dv){
        //cout << pathmin << " vs " << tab[compnum].dv << " of " << last << endl;
        pathmin = tab[previous].dv;
       }
       //cout << "vertex " << last << " previous " << previous << endl;
       tab[last].known = 0;
       last = previous;
       //cout << last << endl;
       if(last != 0)
       previous = tab[previous].pv;
 
    }
 
    tab[0].known = 0;
    //cout << "update " << endl;
    previous = tab[compnum].pv;
    last = compnum;
 
    while(previous != 0){
        for(int t=0; t < nodes[previous].currentSize; t++){
        if(previous == 0){
        //cout << "break 2" << endl;
        break;
        }
 
            if(nodes[previous].dest[t] == last)
            {
        //cout << "if " << last << endl;
                nodes[previous].capacity[t] -= pathmin;
        //cout << " cap " <<  nodes[previous].capacity[t] << endl;
        if((previous > start && previous != compnum) || (previous <= start && last == compnum)){ // backedges
            for(int u= 0; u < nodes[last].currentSize; u++){
                if(nodes[last].dest[u] == previous){   
                        nodes[last].capacity[u] += pathmin;
                //cout <<"vertex vs dest " << last << " " << nodes[previous].dest[u] << endl;
                }
            }
        }
            }
    }
    last = previous;
    previous = tab[previous].pv;
    }
 
/*    while(!q.isEmpty())// update adjacency
    {
//cout << "V and PV " << q.getFront()->getV() << " " << q.getFront()->getPV() << endl;
        //cout << " not empty yet" << endl;
    if(q.getFront()->getV() == 0){//if vertex is phony source
    //cout << "break 1" << endl;
    //cout << q.getFront()->getV() << " " << q.getFront()->getV() << endl;
        q.makeEmpty();
        break;
    }
        for(int t=0; t < nodes[q.getFront()->getPV()].currentSize; t++){
        if(q.getFront()->getPV() == 0){
        //cout << "break 2" << endl;
        break;
        }
 
            if(nodes[q.getFront()->getPV()].dest[t] == q.getFront()->getV())
            {
        //cout << "if " << q.getFront()->getV()<< endl;
        size = nodes[q.getFront()->getV()].currentSize;
                nodes[q.getFront()->getPV()].capacity[t] -= pathmin;
        //cout << " cap " <<  nodes[q.getFront()->getPV()].capacity[t] << endl;
        if((q.getFront()->getPV() > start && q.getFront()->getPV() != compnum) || (q.getFront()->getPV() <= start && q.getFront()->getV() == compnum)){ // backedges
            for(int u= 0; u < nodes[q.getFront()->getV()].currentSize; u++){
                if(nodes[q.getFront()->getV()].dest[u] == q.getFront()->getPV()){  
                        nodes[q.getFront()->getV()].capacity[u] += pathmin;
                //cout <<"vertex vs dest " << q.getFront()->getV() << " " << nodes[q.getFront()->getV()].dest[u] << endl;
                }
            }
        }
            }
        }
        q.dequeue();
 
    }
*/
    for(int w=0; w < start; w++)// update phony source
    {
    int edge = 0;
    edge = nodes[w+1].capacity[0]; 
    for(int t=0; t < nodes[w+1].currentSize; t++)
    {
        if(edge < nodes[w+1].capacity[t])
            edge = nodes[w+1].capacity[t];
    }  
    nodes[0].capacity[w] = edge;
    //cout << "TERMINAL" << nodes[0].dest[w] << endl;
    //cout << "CAPACITY" << nodes[0].capacity[w] << endl;
    }
/*
    for(int i=0; i <= compnum; i++){
    cout << endl;
    cout << i;
        for(int k = 0; k < nodes[i].currentSize; k++){
            cout << " -> " << nodes[i].dest[k] << " [ " << nodes[i].capacity[k] << " ] ";
        if(nodes[i].capacity[k] <= 0)
        cout << "CANT USE : " << i << " to " << nodes[i].dest[k] << endl;
        }
    }

 */
 
 
 
   
    //cout << endl;
 
 
  finalFlow += pathmin;
  //cout << "flow so far " << finalFlow << endl;
  }// while bfs
 
 
  return finalFlow;  // bad result :(
 
 
} // calcMaxFlow()
