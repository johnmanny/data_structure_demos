/*
Author: John Nemeth
Desc: stack header file for stack implementation
Sources: class material and own programming material
*/
#ifndef P2STACK_H
#define P2STACK_H
using namespace std;

class stack
{
	public:
		//constructors/destructors
		stack();
		~stack();
		
		//overloader function for 	
		//mutator funcs
		void push(char& x);	//puts x on stack
		char pop();		//pops x from stack
	
		//accessor functions	
		bool is_empty()const;	//returns bool if stack empty
			
		//assignment operator overload function
		const stack& operator= (stack&);	
		
	private:	
		struct linkedListNode
		{
			char symbol;
			linkedListNode * next;
		};
		linkedListNode * top;
};
#endif
