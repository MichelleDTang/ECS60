#include<iostream>
#include<fstream>
#include"StackAr.h"
#include"QueueAr.h"

using namespace std;

class Row
{
  public:

	int checkr, stat, prow, current;
	
	char pseat;

	StackAr<char> ABC;

	StackAr<char> DEF;
	
	StackAr<char> tempABC;

	StackAr<char> tempDEF;

	Row()
	{
		checkr = 0;
		
		stat = 0;

		prow = 0;

		pseat = ' ';				
		
		current = 0;

		StackAr<char> ABC(3);

		StackAr<char> DEF(3);
		
		StackAr<char> tempABC(2);

		StackAr<char> tempDEF(2);
	}
	
	void clean()
	{
		ABC.makeEmpty();
		DEF.makeEmpty();
	}

	int setnewprow(int r)
	{
		prow = r;
		return prow;
	}

	int getnewprow()
	{
		return prow;
	}

	char setnewpseat(char l)
	{
		pseat = l;
		return pseat;
	}

	char getnewpseat()
	{
		return pseat;
	}

	int setCurrent(int c)
	{
		current = c;
		return current;
	}

	int getCurrent()
	{
		return current;
	}

	int setStatus(int s)
	{
		stat = s;
		return stat;
	}

	int getStatus()
	{
		return stat;
	}

	int setCheck(int rownum)
	{
		checkr = rownum;
		return checkr;
	}

	int getCheck()
	{
		return checkr;

	}

	int Sit(char letter, int match, int state)
	{
		switch(state)
		{
			case 0: break;
			case 1: //cout << "waiting" << endl;
				if(match == 0)
				{
					state = 2;
					break;
				}
				break;
			case 2: //cout << " store 1 " << endl;
				state = 3; 
				break;
			case 3: //cout << "store 2" << endl;
				if(letter == 'A')
				{
					if(!ABC.isEmpty())
					{
						state = 5; break;
					}
					else
					{
						ABC.push(letter);
						state = 7; break;

					}
				}
				else if(letter == 'F')
				{
					if(!DEF.isEmpty())
					{
						state = 5; break;
					}
					else
					{
						DEF.push(letter);
						state = 7; break;

					}
				}
				else if(letter == 'B')
				{
					if(!ABC.isEmpty())
					{
						if(ABC.top() == 'C')
						{
							state = 5; break;
						}
						else
						{
							ABC.push(letter);
							state = 7; break;
						}
					}
					else
					{
						ABC.push(letter);
						state = 7; break;
					}
				}
				else if(letter == 'E')
				{
					if(!DEF.isEmpty())
					{
						if(DEF.top() == 'D') 
						{	
							state = 5; 
							break;
						}
						else
						{
							DEF.push(letter);
							state = 7; break;
						}
					}
					else
					{
						DEF.push(letter);
						state = 7;
						break;
					}
				}
				else
				{
					if(letter == 'C')
					{
						ABC.push(letter);
						state = 7;
						break;
					}
					if(letter == 'D')
					{	
						DEF.push(letter);
						state = 7; 
						break;
					}
				}
			
			case 4: //cout << "sitting " << endl;
				if( letter == 'A' || letter == 'B' || letter == 'C')
				{
					ABC.push(letter);
					if(!tempABC.isEmpty())// if someone is in the aisle
					{
						ABC.push(tempABC.topAndPop());	
						if(!tempABC.isEmpty()) // two people in aisle
						{
							state = 6; 
							break;
						}
						else
						{
							state = 7;
							break;
						}
					}
					else
					{
						ABC.push(letter);
						state = 7; break;
					}
				} 
				else
				{
					DEF.push(letter); // person goes in
					if(!tempDEF.isEmpty()) // if someone is outside
					{
						DEF.push(tempDEF.topAndPop());
						if(!tempDEF.isEmpty())
						{
							state = 6;
							break;
						}
						else
						{
							state = 7;
							break;
						}
					}
					else
					{
						DEF.push(letter);
						state = 7;
						break;
					}
				}
				
			case 5: //cout << "out " << endl; 
				if(letter == 'A' || letter == 'B')
				{
					if(letter == 'A')
					{
					//	if(ABC.top() == 'C' || ABC.top() == 'B')
					//	{
							if(!ABC.isEmpty()) //if there's someone sitting
							{
								tempABC.push(ABC.topAndPop());
								if(!ABC.isEmpty()) //if there's still someone sitting
								{
									state = 5; //double out
									break;
								}
								else
								{
									state = 4; // person sits
									break;
								}
							}
							else
							{
								state = 4;
								break;
							}
					//	}
					}

				
					else
					{
						tempABC.push(ABC.topAndPop());
						state = 4;
						break;
					}
				}
				else
				{
					if(letter == 'F')
					{
					//	if(DEF.top() == 'D' || ABC.top() == 'E')
					//	{
							if(!DEF.isEmpty()) //someone blocking
							{
								
								tempDEF.push(DEF.topAndPop());
								if(!DEF.isEmpty())
								{
									state = 5;
									break;
								}
								else
								{
									state = 4;
									break;
								}
							}
							else
							{
								state = 4;
								break;
							}
					//	}
					}
					else
					{
						tempDEF.push(DEF.topAndPop());
						state = 4;
						break;
					}
				}
			case 6:	
				{	
					
					if(letter =='A' || letter == 'B' || letter == 'C')
					{
						ABC.push(tempABC.topAndPop());
						if(!tempABC.isEmpty())
						{
							state = 7;
							break;
						}
						else
						{
							state = 7;
							break;
						}
					}
					else
					{
						DEF.push(tempDEF.topAndPop());
						if(!tempDEF.isEmpty())
						{
							state = 7;
							break;
						}
						else
						{
							state = 7;
							break;
						}
					}
				}
			
					
	}	
	return state;			
}



};


int main(int argc, char **argv)
{
Row * r;
int stat =0, people =0, print = 0, row, plane = -5;

char seat;

Queue<int> passN(288);

Queue<char> passL(288);

Queue<int> track(48);

Queue<Row *> p(48);
		

ifstream inf(argv[1]);


	for (int pt = 48; pt > 0 ; pt--)
	{
		Row *r = new Row;

		r -> setCheck(pt);

		p.enqueue(r);

		p.getFront() -> setStatus(0);
	}
	

	while (print != 3)
	{
		for(int q = 0; q < 288; q++)
		{
			inf >> row >> seat;
			passN.enqueue(row);
			passL.enqueue(seat);
		}
		people = 0;		
		plane = -5;		

		for(int v = 0; v < 48; v++)
		{
			p.getFront()->clean();
			r = p.getFront();
			p.dequeue();
			p.enqueue(r);
		}

		while(people < 288)		
		{
			for(int y= 0; y < 48; y++)
			{
				//cout << p.getFront()->getnewprow() << " "  << p.getFront() -> getnewpseat() << " " << p.getFront()->getCheck() << " Status: " << p.getFront()->getStatus() << endl;
				if (p.getFront()->getCheck() == 48)
				{
					if(p.getFront()->getStatus() == 0) //row 48 has no one
					{
						r = p.getFront();
						p.dequeue();
					}
					else
					{
							stat = p.getFront() -> Sit(p.getFront() -> getnewpseat(), 0, p.getFront() -> getStatus());
							if (stat == 7)
							{
								p.getFront() -> setStatus(0);	
								p.getFront() -> setnewprow(0);
								p.getFront() -> setnewpseat(' ');
								people++;
								r = p.getFront();
								p.dequeue();		
								//cout << "finished sitting" << endl;
							}	
							else
							{
								p.getFront() -> setStatus(stat);			
								r = p.getFront();
								p.dequeue();
								//cout << "sitting in progress" << endl;
							}						
					}
				}

				else 
				{
					if(p.getFront()->getStatus() == 0) // row is empty
					{
						p.enqueue(r);
						r = p.getFront();
						p.dequeue();
					}
					else
					{
						if(p.getFront()->getCheck() == p.getFront()->getnewprow())
						{
							stat = p.getFront() -> Sit(p.getFront() -> getnewpseat(), 0, p.getFront() -> getStatus());
							if (stat == 7)
							{
								p.getFront() -> setStatus(0);
								p.getFront() -> setnewprow(0);
								p.getFront() -> setnewpseat(' ');
								people++;
								p.enqueue(r);
								r = p.getFront();
								p.dequeue();
								//cout << "finished sitting" << endl;
							}
							else
							{
								p.getFront()->setStatus(stat);
								p.enqueue(r);
								r = p.getFront();
								p.dequeue();
								//cout << "sitting in progress" << endl;
							}
						}
						else
						{

							if(r->getStatus() == 0) // if row in front is empty
							{
								r->setStatus(1);
								p.getFront()->setStatus(0);
								r->setnewprow(p.getFront()->getnewprow());
								r->setnewpseat(p.getFront()->getnewpseat());
								p.getFront()-> setnewprow(0);
								p.getFront()-> setnewpseat(' ');
								p.enqueue(r);
								r = p.getFront();
								p.dequeue();
								//cout << "move forward" << endl;
							}
							else
							{
								p.enqueue(r);
								r = p.getFront();
								p.dequeue();
								//cout << "stay put" << endl;
							}

						}
					}
				}
			}
			if(r->getStatus() == 0)
			{
				if(!passN.isEmpty())
				{
					r->setnewprow(passN.getFront());
					passN.dequeue();
					r->setnewpseat(passL.getFront());
					passL.dequeue();
					r->setStatus(1);			
					p.enqueue(r);
					//cout << "next passenger was added" << endl;
				}
				else
				{
					p.enqueue(r);
					//cout << "no more passengers to add" << endl;
				}
			}
			else
			{
				p.enqueue(r);
				//cout << "someone's at row 1" << endl;
			}
			plane += 5;
			//cout << plane << endl;
			//cout << people << endl;
		}

		plane += 5;

		switch(print)
		{
			case 0:cout << "Back to front: " << plane << endl; break;
			case 1: cout << "Random: " << plane << endl; break;
			case 2: cout << "Outside in: "<< plane << endl; break;
		}	
		print ++;
		plane = 0;

	}

	

	return 0;
}


