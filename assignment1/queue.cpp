/*
	Author: John Nemeth
	Desc: implementation file of queue.h. commented out portions of code I might need for future assignments.
	Source files: own material.  
*/
#include <iomanip>
#include <cstring>
#include "queue.h"
#include <iostream>


//constructors/destructors
queue::queue()
{
	head = NULL;
}

queue::~queue()
{
	node * cur = head;
	while(head)
	{
		cur = head->next;
		delete head;
		head = cur;
	}
}

//mutators
void queue::enqueue(int& x)
{
	node * cur = new node;
	cur->entry = x;
	cur->next = NULL;
	if (!head) {
		head = cur;
		head->next = NULL;
	}
	else {
		node * cur2 = head;
		while (cur2->next) 
			cur2 = cur2->next;
		cur2->next = cur;
	}	
}

int queue::dequeue()
{
	int x = 0;
	if (!head) {
		return is_empty();
	}
	else
	{
		x = head->entry;
		node * cur = head;
		head = head->next;
		delete cur;
		return x;
	} 
}

//accessors
bool queue::is_empty()const
{
	if (!head)
		return true;
	else
		return false;
}
