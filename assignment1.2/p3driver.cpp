/*
	Author: John Nemeth
	Description: driver file for restaurant assignment
	sources: class material and previous classwork 
*/

#include <iostream>
#include "queue.h"
#include <fstream>
#include <string>

//main function with command line arguments. int argc is number of arguments " ./a.out problem1-1.input" ./a.out is argument 0, problem1-1.input is arg 1, etc.
int main(int argc, char* argv[]) {
	
	ifstream in;
	const int MAX = 10;
	queue theQueue;
	
	//if there is no command line argument other than the execution of the program
	if (argc == 1)
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;
	
	//open the second command line argument, which is the filename
	in.open(argv[1]);
	if (!in)	
		cout << "Failed to open " << argv[1] << endl;
	else {
		int numLines = 0, rest = 0, total = 0, energy = 0, distance = 0, index = 0;
		in >> numLines;
		in.ignore(MAX, '\n');
		while (index < numLines) {		//loop to enqueue totals from energy and distance subtraction
			in >> energy;
			in >> distance;
			in.ignore(MAX, '\n');
			total = energy - distance;
			theQueue.enqueue(total);
			index++;
		}
		//index = 0;
		total = 0;
		for (index = 0; index < numLines; index++) {		//loop to successively add totals and check if total is negative or zero
			total = total + theQueue.dequeue();
			if (total <= 0) {
				rest = index + 1;	
				total = 0;
			}
		}
		cout << rest << endl;
	}
	in.close();
	return 0;
	
}
