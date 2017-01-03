//hash for p5
 
#include "vector.h"
 
using namespace std;
 
class HashTable
{
    private:
   
        unsigned int tableSize= 16776960, size=0;
        int pos;
 
        int* array = new int[16776960];
       
   
 
    public:
        HashTable(){}
 
 
        void insert (const char* Address, int i){
            intValue(Address);
            unsigned int hashValue = intValue(Address);
            int index = hashValue % tableSize;
            array[index] = i;
           
 
        }
 
        int getIndex(const char* Address){
           
            unsigned int hashValue = intValue(Address);
            int index = hashValue % tableSize;
            return array[index];
        }
           
 
 
 
 
 
 
        int intValue(const char* Address)
        {
       
           
 
            int bits[5];
            int j = 0;
            int convert = 0;
            unsigned int shift = 0;
            for(int i = 0; i < 16; i++){
                if(j == 4)
                    break;
                if(Address[i] != '.' && (Address[i] > 47 && Address[i] < 58) ){
                    convert += (Address[i] - 48);
                    convert *= 10;
                }
                else{
                if(Address[i] == '.' || Address[i] == '\0'){
                //  if(Address[i] != '\000'){
                        convert /= 10;
                    }
                    bits[j] = convert;
                    convert = 0;
                    j++;
                }
 
 
 
            }

            shift = shift|(bits[0] << 24);
            shift = shift|(bits[1] << 16);
            shift = shift|(bits[2] << 8);
            shift = shift|(bits[3]);
            //cout << "MY INT VALUE IS" << shift << endl;
            return shift;  
 
 
 
        }
};
