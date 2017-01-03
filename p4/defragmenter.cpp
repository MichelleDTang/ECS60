#include<iostream>
#include"defragmenter.h"
#include"DefragRunner.h"
#include "myhash.h"
#include "hashplace.h"
#include "indexhash.h"

using namespace std;

Defragmenter::Defragmenter(DiskDrive *diskDrive)
{
  index = 2;
  write = 0;
  read = 0;
  emptyindex = 0;
  cap = diskDrive->getCapacity();
  filenum = diskDrive->getNumFiles();
  IndexHashTable nextindex;
  HashTable myhash;
  PlaceHashTable place;  

  for(int i= 2; i< cap; i++)
  {
    if(diskDrive->FAT[i] == false)
    {
      empty[emptyindex] = i;
      emptyindex++;
    }
  } 

  for(int i=0; i<filenum; i++) //go by directory[]
  {
    block = diskDrive->directory[i].getFirstBlockID();
    diskDrive->directory[i].setFirstBlockID(index);
    while(block != 1)
    {
      if(index < block)
      {
        blockptr = diskDrive->readDiskBlock(block);
	read++;
        diskDrive->FAT[block] = false;
	empty[emptyindex] = block;
	emptyindex++;
        block = blockptr->getNext();
        if(block != 1)
          blockptr->setNext(index+1);
      }// look at disk[]
      else if(index > block)
      {
	if( nextindex.find(block) != 0){
		if(nextindex.find(block) == index){
			blockptr = diskDrive->readDiskBlock(nextindex.find(block));
	read++;
			write = 1;
		}
		else {
			blockptr = diskDrive->readDiskBlock(nextindex.find(block));
	read++;
			diskDrive->FAT[nextindex.find(block)] = false;
			empty[emptyindex] = nextindex.find(block);
			emptyindex++;
		}
	}	
	else
	{
		blockptr = myhash.find(place.find(block));
	}
	block = blockptr->getNext(); // get next from nexthash
        if(block != 1)
          blockptr->setNext(index+1);
      }// look at hash
      else
      {
        blockptr = diskDrive->readDiskBlock(block);
	read++;
        block = blockptr->getNext();
        if (block != 1)
          blockptr->setNext(index+1);
	write = 1;
      }// don't do anything cuz i == block
      if(diskDrive->FAT[index] == false)
      {
        diskDrive->writeDiskBlock(blockptr, index);

        delete blockptr;
        diskDrive->FAT[index] = true;
      }
      else
      {
	if(write == 0)
	{
	        temp = diskDrive->readDiskBlock(index);	
		diskDrive->FAT[index] = false;
	read++;
		diskDrive->writeDiskBlock(blockptr, index);
		diskDrive->FAT[index] = true;
		delete blockptr;
		int tableSize = myhash.getCurrentSize();
		if(tableSize < 13250)// put into pointer hash
		{
		        myhash.insert(*temp);
			place.insert(index, tableSize);
		}
		else{//disk allocate insert
					counter = emptyindex-1;
					for( int i = counter; i > 0; i--){
						if(diskDrive->FAT[empty[i]] == false){
							emptyindex = i;
							break;
						}
					}	
					diskDrive->writeDiskBlock(temp, empty[emptyindex]);

					nextindex.insert(index, empty[emptyindex]);	
					diskDrive->FAT[empty[emptyindex]] = true;
		}
		  
		delete temp;
	} 
	else
	{
                delete blockptr;
		write =0;
	}
      }
      
      index++;
    }
  }
  for(int i = index; i < cap; i++)
    if(diskDrive->FAT[i] == true)
      diskDrive->FAT[i] = false;

}
