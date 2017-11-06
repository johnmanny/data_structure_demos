/*
author:
sources:
desc:
*/

#ifndef RBTREE_H
#define RBTREE_H

using namespace std;

class rbTree
{
	public:
		//constructors/destructors
		rbTree();
		~rbTree();

		//assignment requirements
		void insert(int);
		void remove(int);
		bool search(int);
		int maximum();
		int minimum();

	private:
		//secondary mutator functions
		void insertFix(node *);
		void leftRotate(node *);
		void rightRotate(node *);
		void removeFix(node *);

		//rb tree node
		struct node
		{
			int key;
			char color;
			node * left;
			node * right;
			node * parent;
		}
		node * root;
}
