// Michelle Tang
// Christina Hardiman 
// Driver program that asks for a filename and repeatedly asks the user for the ADT to which he/she wishes to apply the ammands from the specified file.

#include<iostream>
#include<fstream>
#include"vector.h"
#include"LinkedList.h"
#include"dsexceptions.h"
#include"StackAr.h"
#include"CursorList.h"
#include"QueueAr.h"
#include"StackLi.h"
#include"SkipList.h"
#include"CPUTimer.h"
#include<string>

using namespace std;

vector<CursorNode <int> > cursorSpace(500000);

int getChoice()
{
	int choose;
	cout << "      ADT Menu" << endl;
	cout << "0. Quit" << endl;
	cout << "1. LinkedList" << endl;
	cout << "2. CursorList" << endl;
	cout << "3. StackAr" << endl;
	cout << "4. StackLi" << endl;
	cout << "5. QueueAr" << endl;
	cout << "6. SkipList" << endl;
	cout << "Your choice >> ";
	cin >> choose;	
		
	return choose;
}
void RunList(char * filename)
{
	char command, first[512];
	int num;
	List <int> list;
	ListItr <int> listItr = list.zeroth();
	ifstream read(filename);
	read.getline(first,512);
	while (read >> command >> num)
	{
		if (command == 'i')
		{
			list.insert(num, listItr);
		}
		else	
		{
			list.remove(num);	
		}
	}	
}
// is erroring with accessing outside array with testhw
void RunCursorList(char * filename)
{
	char command, first[512];
	int num;
	CursorList<int> object(cursorSpace);
	CursorListItr<int> cursItr = object.zeroth();
	ifstream read(filename);
        read.getline(first,512);	
	while (read >> command >> num)
	{
		if (command == 'i')
		{
			object.insert(num, cursItr);
		}
		if (command == 'd')
		{
			object.remove(num);
		}
	}	
}

void RunStackAr(char * filename)
{
	char command, first[512];
	int num;
	ifstream read(filename);
	StackAr<int> object(500000);
	read.getline(first,512);	
	while (read >> command >> num)
	{
		if (command == 'i')
		{
			object.push(num);	
		}
		if (command == 'd')
		{
			object.pop();	
		}
	}	
}

void RunStackLi(char * filename)
{
	char command, first[512];
	int num;
	StackLi<int> object;
	ifstream read(filename);	
	read.getline(first,512);
	while (read >> command >> num)
	{
		if (command == 'i')
		{
			object.push(num);
		}
		if (command == 'd')
		{
			object.pop();
		}	
	}
}

void RunQueueAr(char * filename)
{
	char command, first[512];
	int num;
	Queue<int> object(500000);
	ifstream read(filename);	
	read.getline(first,512);
	while (read >> command >> num)
	{
		if (command == 'i')
		{
			object.enqueue(num);
		}
		if (command == 'd')
		{
			object.dequeue();
		}
	}
}

void RunSkipList(char * filename)
{
	char command, first[512];
	int num;
	SkipList<int> object(0 , 1000000 );
	ifstream read(filename);
	read.getline(first,512);
	while (read >> command >> num);
	{
		if (command == 'i')
		{
			object.insert(num);
		}
		if (command == 'd')
		{
			object.deleteNode(num);
		}
	}	
}

int main()

{	
	char a[1000];	
	cout << "Filename >> ";
	cin >> a;
	
	int choice;
	CPUTimer ct;	

	do
	{
		cout << endl;
		choice = getChoice();
		ct.reset();
		switch (choice)
		{
			case 1: RunList(a); break;
			case 2: RunCursorList(a); break;
			case 3:	RunStackAr(a); break;
			case 4:	RunStackLi(a); break;
			case 5:	RunQueueAr(a); break;
			case 6:	RunSkipList(a); break;
		 }

		cout << "CPU time: " << ct.cur_CPUTime() << endl ;
	} while(choice > 0);	

} 


