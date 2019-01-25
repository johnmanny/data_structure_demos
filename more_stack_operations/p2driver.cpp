/*
	Author: John Nemeth
	Description: driver file for well ordered brackets
	sources: class material and http://www.programmingnotes.org/?p=1879 for statement semi-template 
*/

#include <iostream>
#include "p2stack.h"
#include <fstream>
#include <string>

//main function with command line arguments. int argc is number of arguments " ./a.out problem1-1.input" ./a.out is argument 0, problem1-1.input is arg 1, etc.
int main(int argc, char* argv[]) {
	
	ifstream in;
	const int MAX = 10;
	stack theStack;
	bool passed = true, newlined = false;
	string newlineCheck;
	
	//if there is no command line argument other than the execution of the program
	if (argc == 1)
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;
	
	//open the second command line argument, which is the filename
	in.open(argv[1]);
	if (!in)	
		cout << "Failed to open " << argv[1] << endl;
	else {
		char symbol = 'a', stackSymbol;
		int numLines = 0;
		in >> numLines;
		in.ignore(MAX, '\n');
		for (int index = 0; index < numLines; index++) {
			passed = true;
			while (passed) { 	
				in.get(symbol);
				if (symbol == '\n') {
					break;
				}
				if ((symbol == '<') || (symbol == '(') || (symbol == '{') || (symbol == '[')) 
					theStack.push(symbol);		//push symbol if it an opening symbol
				else {
					if (theStack.is_empty())
						passed = false;
					else {
						stackSymbol = theStack.pop();		//pop symbols successively to determine if they fit with input closing symbols, if relevant symbols were input
						if ((symbol == ')') && (stackSymbol != '('))
							passed = false;		
						else if ((symbol == '}') && (stackSymbol != '{'))	
							passed = false;
						else if ((symbol == ']') && (stackSymbol != '['))
							passed = false;
						else if ((symbol == '>') && (stackSymbol != '<'))
							passed = false;
					}
				}
			}
			if (symbol != '\n') {
				in.ignore(MAX, '\n');
			}		
			while (!theStack.is_empty())
				theStack.pop();
			if (passed == true) {
				cout << "YES" << endl;
			}
			else if (passed == false) {
				cout << "NO" << endl;	
			}
		}
	in.close();
	return 0;
	}
}
