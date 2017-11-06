/*
	Author: John Nemeth
	Description: driver file for linked list implementation of stack demonstration. in other words, driver file for assignment1 in cis313
	sources: class material and assignment guidelines, http://www.cplusplus.com/articles/DEN36Up4/ for command line argument information
*/

#include <iostream>
#include "stack.h"
#include <fstream>
#include <cstring>

//func prototype to print stack, takes reference of existing stack
void printStack(stack& aStack);

//main function with command line arguments. int argc is number of arguments " ./a.out problem1-1.input" ./a.out is argument 0, problem1-1.input is arg 1, etc.
int main(int argc, char* argv[]) {
	
	ifstream in;
	const int MAX = 10;
	stack fromFile;
	
	//if there is no command line argument other than the execution of the program
	if (argc == 1)
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;
	
	//open the second command line argument, which is the filename
	in.open(argv[1]);
	if (!in)	
		cout << "Failed to open " << argv[1] << endl;
	else {
		int pushVal = 0, popVal = 0;
		char command[MAX];
		while (!in.eof()) {
			//get first two characters of current line from file
			in.get(command, 3, '\n');
			//if push, get number by moving cursor to space before number and then getting number. 
			if (strstr(command, "pu")) {
				in.ignore(MAX, ' ');
				in >> pushVal;
				fromFile.push(pushVal);	
			}			
			else if (strstr(command, "po")) {
				if (fromFile.is_empty())
					cout << "StackError";
				else {
					cout << fromFile.pop() << " ";
				}
				cout << endl;
			}
		 	else if (strstr(command, "pr")) {
				printStack(fromFile);
				cout << endl;
			}
			in.ignore(MAX, '\n');	
		}
	}	
	in.close();
	return 0;
}

//print stack by popping from input stack and pushing values into newly made stack
void printStack(stack& aStack) {

	if (aStack.is_empty())
		cout << "Empty";
	else {
		int popVal[50] = {0}, index = 1;
		stack newStack;
		//put values into array to push into new stack in correct order
		while (!aStack.is_empty()) {
			popVal[index] = aStack.pop();
			cout << popVal[index] << " ";
			index++;
		}
		while (index > 1) {
			index--;
			newStack.push(popVal[index]);
		}
		aStack = newStack;	
	}
}	
