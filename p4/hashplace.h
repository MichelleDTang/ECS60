// int gash

#include "mynew.h"

class PlaceHashTable
{

	private:

		int array[500000];

		int currentSize, hashed, tableSize, counter;
	
	public:
		PlaceHashTable(){ 

			currentSize = 0;
			hashed = 0;
			tableSize= 500000;
		}

		void insert(int next, int hashindex)
		{
			array[next] = hashindex;
			currentSize++;

		}

		int gethashed()
                {
			return hashed;
                }

		void remove(int index)
		{
			if( array[index] != 0)
				array[index] = 0;
		}
		
		///int find(int keyValue, int index)
		int find(int OriginalIndex)
		{
			return array[OriginalIndex];// return where that block is in hash
		}


};
