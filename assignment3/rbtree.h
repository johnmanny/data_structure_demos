/*
author:
sources:
desc:
*/

#ifndef RBTREE_H
#define RBTREE_H

using namespace std;

//rb tree node
struct node
{
	int key;
	char color;
	node * left;
	node * right;
	node * parent;
};

class rbTree
{
	public:
		//constructors/destructors
		rbTree();
		~rbTree();

		//assignment requirements
		void insert(int);
		bool remove(int);
		bool search(int);
		int maximum();
		int minimum();

		//accessor functions
		void print();

	private:
		// called inside fix funcs
		void insertFix(node *&);
		void removeFix(node *&);

		// node utility functions (node funcs return pointers)
		node *findNodeByKey(int);
		node *findSuccessor(node *);
		node *findMinNode(node *);
		node *findMaxNode(node *);
		void leftRotate(node *&);
		void rightRotate(node *&);
		void transplant(node *&, node *&);

		// other functions
		void destroyTree(node *&);
		void inOrderPrint(node *);

		node * root;
		node * nil;
};
#endif
