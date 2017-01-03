// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"
class Defragmenter
{
	public:
  		int cap, filenum, index, block, newLocation, write, counter, empty[250000], emptyindex, read;  
  		DiskBlock *blockptr, *temp;

  		Defragmenter(DiskDrive *diskDrive);

}; // class Defragmenter
#endif
