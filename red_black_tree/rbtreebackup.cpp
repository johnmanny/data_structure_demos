/*
author:
sources:
description:
*/

#include "rbtree.h"
#include <iostream>
#include <iomanip>

//constructor/destructors//////////////
rbTree::rbTree() {
	root = NULL;
	nil = NULL;
	nil->color = 'b';
}

rbTree::~rbTree() {
	destroyTree(root);
}

//utility functions
void rbTree::destroyTree(node *& tempNode) {
	if (tempNode) {
		destroyTree(tempNode->left);
		destroyTree(tempNode->right);
		delete tempNode;
	}
}

//insert key
void rbTree::insert(int x) {
	node * cur = new node;
	cur->parent = NULL;
	cur->left = NULL;
	cur->right = NULL;
	cur->key = x;
	cur->color = 'r';
	node * prev = NULL;
	node * next = root;
	while (next != NULL) {
		prev = next;
		if (x < next->key)
			next = next->left;
		else
			next = next->right;
	}
	if (prev == NULL)
		root = cur;
	else if (cur->key < prev->key) {
		prev->left = cur;
		cur->parent = prev;
	}
	else {

		prev->right = cur;
		cur->parent = prev;
	}
	//output key and color about to be insertfixed
	cout << "about to insertfix: " << cur->key << "color: " << cur->color << endl;
	insertFix(cur);
}

//insertfix
void rbTree::insertFix(node * cur) {
	//root always black
	if (cur == root) {
		cur->color = 'b';
		return;
	}
	//while parent is red
	while ((cur->parent->color == 'r') && (cur != root)) {
		//if cur's parent is leftchild 
		node * other = NULL;
		if (cur->parent == cur->parent->parent->left) {
			other = cur->parent->parent->right;
			//if cur's uncle is red(parent already red), change parent and uncle to black and grandparent to red
			if (other->color == 'r') {
				cur->parent->color = 'b';
				other->color = 'b';
				cur->parent->parent->color = 'r';
				cur = cur->parent->parent;
			}
			//if cur is rightchild
			else if (cur == cur->parent->right) {
				cur = cur->parent;
				leftRotate(cur);
				cur->parent->color = 'b';
				cur->parent->parent->color = 'r';
				rightRotate(cur->parent->parent);
			}
		}
		else {
			other = cur->parent->parent->left;
			if (other->color == 'r') {
				cur->parent->color = 'b';
				other->color = 'b';
				cur->parent->parent->color = 'r';
				cur = cur->parent->parent;
			}
			else if (cur == cur->parent->left) {
				cur = cur->parent;
				rightRotate(cur);
				cur->parent->color = 'b';
				cur->parent->parent->color = 'r';
				leftRotate(cur->parent->parent);
			}
		}
	}
	//root to black
	root->color = 'b';		
}

//rotations
void rbTree::leftRotate(node * cur) {
	if (cur->right == NULL)
		return;
	else {
		node * other = cur->right;
		//make other's left child a rightchild of cur
		if (other->left != NULL) {
			cur->right = other->left;
			other->left->parent = cur;
		}
		else
			cur->right = NULL;
		other->parent = cur->parent;
		//check position of cur and place other there
		if (cur->parent == NULL)		//cur is root case
			root = other;
		else if (cur == cur->parent->left)	//cur is parent's left child
			cur->parent->left = other;
		else					//cur is parent's right child
			cur->parent->right = other;
		other->left = cur;
		cur->parent = other;
	}	
}

void rbTree::rightRotate(node * cur) {
	if (cur->left == NULL)
		return;
	else {
		node * other = cur->left;
		//make other's right child a leftchild of cur
		if (other->right != NULL) {
			cur->left = other->right;
			other->right->parent = cur;
		}
		else
			cur->left = NULL;
		other->parent = cur->parent;
		//check pos of cur and place other there
		if (cur->parent == NULL)
			root = other;
		else if (cur == cur->parent->right)
			cur->parent->right = other;
		else
			cur->parent->left = other;
		other->right = cur;
		cur->parent = other;
	}
}

//print function
void rbTree::print() {
	inOrderPrint(root);
	cout << "nil color: " << nil->color << endl;
}

void rbTree::inOrderPrint(node * cur) {
	if (!cur)
		return;
	inOrderPrint(cur->left);
	cout << "key: "<< cur->key << " color: " << cur->color << endl;
	inOrderPrint(cur->right);
}
