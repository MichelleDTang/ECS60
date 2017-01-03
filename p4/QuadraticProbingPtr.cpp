        #include "QuadraticProbingPtr.h"
        #include "mynew.h"
        #include <iostream>
        using namespace std;



        /**
         * Construct the hash table.
         */
        QuadraticPtrHashTable<DiskBlock>::QuadraticPtrHashTable( int size )
          : array(size)
        {
            makeEmpty( );
        }

        QuadraticPtrHashTable<DiskBlock>::~QuadraticPtrHashTable()
        {
          for(int i = 0; i < array.size(); i++)
            if(array[i] != NULL)
              delete (array[i]);
        }

        void QuadraticPtrHashTable<DiskBlock>::insert( const DiskBlock & x, int index)
        {
                // Insert x as active
            int currentPos = findPos( index );
            array[ currentPos ] = new DiskBlock(x);
        
        }
 
        int QuadraticPtrHashTable<DiskBlock>::findPos( int index ) const
        {
/* 1*/      int collisionNum = 0;
/* 2*/      int currentPos = hash( index, array.size( ) );


/* 7*/      return currentPos;
        }

        void QuadraticPtrHashTable<DiskBlock>::makeEmpty()
        {
          for(int i = 0; i < array.size(); i++)
          {
            array[i] = NULL;
          }
        } 
        /**
         * Remove item x from the hash table.
         */
        void QuadraticPtrHashTable<DiskBlock>::remove( int index )
        {
            int currentPos = findPos( index );
            
            delete array[currentPos];
            array[ currentPos ] = NULL;
            
        }

        const HashedObj & QuadraticPtrHashTable<DiskBlock>::find( int index ) const
        {
            int currentPos = findPos( index );
            return array[currentPos];

        }


        int QuadraticPtrHashTable<DiskBlock>::hash( int key, int tableSize ) const
        {
            if( key < 0 ) key = -key;
            return key % tableSize;
        }
