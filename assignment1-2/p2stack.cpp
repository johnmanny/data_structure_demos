/*
	Author: John Nemeth
	Desc: implementation file of stack.h
	Source files: own programming material and class material
*/
#include <iomanip>
#include <cstring>
#include "p2stack.h"
#include <iostream>


//constructors/destructors
stack::stack()
{
	top = NULL;
}

stack::~stack()
{
	linkedListNode * cur = top;
	while(top)
	{
		cur = top->next;
		delete top;
		top = cur;
	}
}

//mutators
void stack::push(char& x)
{
	linkedListNode * cur = new linkedListNode;
	cur->symbol = x;
	cur->next = NULL;
	cur->next = top;
	top = cur;
}

char stack::pop()		//MIGHT NEED REVISION FOR OVERLOADER OF node * cur = top
{
	int x = 0;
	if (!top) {
		return is_empty();
	}
	else
	{
		x = top->symbol;
		linkedListNode * cur = top;
		top = top->next;
		delete cur;
		return x;
	} 
}

//accessors
bool stack::is_empty()const
{
	if (!top)
		return true;
	else
		return false;
}

//assignment overloader function
const stack& stack::operator= (stack& oStack) {
	if (this == &oStack)
		return *this;
	else {
		linkedListNode * cur = top;
		while (top) {
			cur = top->next;
			delete top;
			top = cur;
		}
		if (!oStack.top)
			top = NULL;
		else {
			top = new linkedListNode;
			top->symbol = oStack.top->symbol;
			linkedListNode * newStack = top;
			linkedListNode * oldStack = oStack.top->next;
			while (oldStack) {
				newStack->next = new linkedListNode;
				newStack = newStack->next;
				newStack->symbol = oldStack->symbol;
				oldStack = oldStack->next;
			}
			newStack->next = NULL;
		}
		return *this;
	}
	if (this == &oStack)
		return *this;
}
