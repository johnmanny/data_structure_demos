/*
Author: John Nemeth
Desc: stack header file for stack implementation
Sources: 
*/
#ifndef STACK_H
#define STACK_H
using namespace std;

class stack
{
	public:
		//constructors/destructors
		stack();
		~stack();
		
		//overloader function for 	
		//mutator funcs
		void push(int& x);	//puts x on stack
		int pop();		//pops x from stack
	
		//accessor functions	
		bool is_empty()const;	//returns bool if stack empty
			
		//assignment operator overload function
		const stack& operator= (stack&);	
		
	private:	
		struct linkedListNode
		{
			int entry;
			linkedListNode * next;
		};
		linkedListNode * top;
};
#endif
