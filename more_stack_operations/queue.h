/*
Author: John Nemeth
Desc: queue header file for stack implementation
Sources:	own material 
*/
#ifndef QUEUE_H
#define QUEUE_H
using namespace std;

class queue
{
	public:
		//constructors/destructors
		queue();
		~queue();
		
		//mutator funcs
		void enqueue(int& x);	//enqueue value
		int dequeue();		//dequeue value from queue and output
	
		//accessor functions	
		bool is_empty()const;	//returns bool if queue empty
		
	private:	
		struct node
		{
			int entry;
			node * next;
		};
		node * head;
};
#endif
