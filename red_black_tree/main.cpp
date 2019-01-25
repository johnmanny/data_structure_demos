/*
author: John Nemeth
sources: class notes, previous projects,
	  http://www.geeksforgeeks.org/c-program-red-black-tree-insertion/	
description: driver file for RBtree implementation.
		print function is implemented and called as a 
		class function for better modularity, security,
		and because copy constructors are a pain. no whitespace,
		though!
		
*/

#include <iostream>
#include "rbtree.h"
#include <fstream>
#include <cstring>

int main(int argc, char* argv[]) {

	const int MAXCHARS = 10;
	ifstream in;
	rbTree tree;

	// check if filename argument is present
	if (argc == 1)
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;

	in.open(argv[1]);
	if (!in)
		cout << "failed to open " << argv[1] << endl;
	else {
		int key = 0;
		char command[MAXCHARS];
		while (!in.eof()) {
			
			// get first 3 chars from line
			in.get(command, 3, '\n');
			if (strstr(command, "in")) {
				in.ignore(MAXCHARS, ' ');
				in >> key;
				tree.insert(key);
			}
			else if (strstr(command, "re")) {
				in.ignore(MAXCHARS, ' ');
				in >> key;
				if (tree.remove(key) == false)
					cout << "TreeError" << endl;
			}
			else if (strstr(command, "se")) {
				in.ignore(MAXCHARS, ' ');
				in >> key;
				if (tree.search(key) == false)
					cout << "NotFound" << endl;
				else
					cout << "Found" << endl;
			}
			else if (strstr(command, "ma")) {
				tree.maximum();
			}
			else if (strstr(command, "mi")) {
				tree.minimum();
			}
			else if (strstr(command, "pr")) {
				tree.print();
			}
		in.ignore(MAXCHARS, '\n');
		}
	in.close();
	}
	return 0;
}

