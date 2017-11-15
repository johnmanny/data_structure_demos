/*
author:
sources:
description:
*/

#include <iostream>
#include "rbtree.h"
#include <fstream>
#include <cstring>

int main(int argc, char* argv[]) {

	const int MAXCHARS = 10;
	ifstream in;
	rbTree tree;

	// if no file given in command line argument
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
			//cout << command << endl;
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

	/*
	cout << "testing" << endl;
	tree.insert(5);
	tree.print();
	tree.insert(6);
	tree.print();
	tree.insert(1);
	tree.print();
	tree.insert(40);
	tree.print();
	tree.insert(35);
	tree.print();
	tree.insert(2);
	tree.print();
	tree.insert(20);
	tree.print();
	tree.remove(2);
	tree.remove(5);
	tree.print();
	if (tree.remove(11))
		cout << "removed" << endl;
	else
		cout << "error" << endl;
	
	*/
	return 0;
}

