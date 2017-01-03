// Author: Sean Davis
#ifndef maxfinderH
#define maxfinderH
#include "NetDriver.h"
#include <cstring>
#include "maxheap.h"
#include "myhash.h"

using namespace std;

struct Node
{
    string address;
    int dest[15000];
    short currentSize;
    short capacity[15000];
   
};


struct Table
{
    int known=0;
    int dv = 0;
    int pv = 0;

};

class MaxFinder
{
  HashTable myhash;
  bool bfs;
  int compnum, start, pathmin, finalFlow, previous;
  int vertex, sink, last;
  bool check;
  //string ips[15000];
  Node* nodes;
  Table* tab;

public:
  
  MaxFinder(const Computer *computers, int numComputers, int numTerminals);
  int calcMaxFlow(Edge *edges, int numEdges);
}; // class MaxFinder




#endif
