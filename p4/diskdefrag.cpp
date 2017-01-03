#include<iostream>
#include"defragmenter.h"
#include"DefragRunner.h"
#include "myhash.h"
#include "myinthash.h"
#include "hashplace.h"
#include "indexhash.h"

using namespace std;

Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
  index = 2;
  write = 0;
  cap = diskDrive->getCapacity();
  filenum = diskDrive->getNumFiles();
  IndexHashTable nextindex;
  HashTable myhash;
  PlaceHashTable place;  
 
  for(int i=0; i<filenum; i++) //go by directory[]
  {
    block = diskDrive->directory[i].getFirstBlockID();
    diskDrive->directory[i].setFirstBlockID(index);
    while(block != 1)
    {
	cout << "index " << index << " block " << block << endl;
      if(index < block)
      {
        blockptr = diskDrive->readDiskBlock(block);
        diskDrive->FAT[block] = false;
	previous = block;
        block = blockptr->getNext();
        if(block != 1)
          blockptr->setNext(index+1);
      }// look at disk[]
      else if(index > block)
      {

        cout << index << " " << block << endl;
		cout << "In INTHASHTABLE, USING THIS INDEX TO FIND VALUE: " << block << endl;
		cout << "find worked!" << endl;
		blockptr = diskDrive->readDiskBlock(nextindex.find(block));
		diskDrive->FAT[nextindex.find(block)] = false;
		cout << "retreived from disk " << endl;
	previous = block;
	block = blockptr->getNext(); // get next from nexthash
        cout << "block " << block << endl;
	cout << "index " << index << endl;
        if(block != 1)
          blockptr->setNext(index+1);
      }// look at hash
      else
      {
        blockptr = diskDrive->readDiskBlock(block);
	previous = block;
        block = blockptr->getNext();
        if (block != 1)
          blockptr->setNext(index+1);
	write = 1;
      }// don't do anything cuz i == block
      if(diskDrive->FAT[index] == false)
      {
        diskDrive->writeDiskBlock(blockptr, index);
        //delete blockptr;
        diskDrive->FAT[index] = true;
      }
      else
      {
	if(write == 0)
	{
	        temp = diskDrive->readDiskBlock(index);
		int currentIndex = index;
		unsigned nextValue = temp->getNext();
		int tableSize = myhash.getCurrentSize();
			for(int i = index; i < cap; i++){
				if( diskDrive->FAT[i] == false)
				{
					cout << "filenum " << temp->getFileBlockNum() << " next " << nextValue << endl;
					diskDrive->writeDiskBlock(temp, i);
					cout << index << " " << i << endl;
					nextindex.insert(index, i);	
					diskDrive->FAT[i] = true;
					break;
				}
			}
			cout << "break " << endl;
		delete temp;
  	      diskDrive->writeDiskBlock(blockptr, index);
	}
	else
	{
		write =0;
	}
        delete blockptr;
	diskDrive->FAT[index] = true;
      }
      index++;
    }
  }
  for(index = index; index < cap; index ++)
    diskDrive->FAT[index] = false;

}
