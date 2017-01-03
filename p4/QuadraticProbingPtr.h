        #ifndef _QUADRATIC_PROBING_PTR_H_
        #define _QUADRATIC_PROBING_PTR_H_

        #include "vector.h"
        #include "mystring.h"

        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings
        class QuadraticPtrHashTable
        {
          public:
            QuadraticPtrHashTable( const DiskBlock & notFound, int size = 1000000);
            ~QuadraticPtrHashTable();
            void makeEmpty( );
            void insert( const DiskBlock & x , int index);
            void remove( int index);

//            const QuadraticPtrHashTable & operator=( const QuadraticPtrHashTable & rhs );

          private:
            vector<const DiskBlock*> array;
            int currentSize;
            int findPos( int index ) const;
            int hash( int key, int tableSize ) const;
        };

        #include "QuadraticProbingPtr.cpp"
        #endif
