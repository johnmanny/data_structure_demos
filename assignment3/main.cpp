/*
author:
sources:
description:
*/

#include <iostream>
#include "rbtree.h"
//#include <fstream>

int main() {
	rbTree tree;
	
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
	tree.remove(11);
	return 0;

}

