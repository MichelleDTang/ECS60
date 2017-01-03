// Header for own hash


#include "mynew.h"
#include "vector.h"

using namespace std;

class HashTable
{
	private:
		vector<DiskBlock*> array;
		int currentSize;


	public:
		HashTable(unsigned size):array(size){ makeEmpty(); }

/*		~HashTable(){
			for(int i = 0; i < array.size(); i++){
				if(array[i] != NULL)
					delete array[i];
			}		}
*/
		void makeEmpty()
		{
			currentSize = 0;
			for(int i = 0; i < array.size(); i++)
			array[i] = NULL;
		}

		void insert(DiskBlock & currentBlock, int index)
		{
			if(array[index] != NULL)
				return;

			array[index] = new DiskBlock(currentBlock);
		}

		void remove(int index)
		{
			if( array[index] != NULL)
				delete array[index];
		}
		
		DiskBlock * find(int index)
		{
			return array[index];

		}



	
};
