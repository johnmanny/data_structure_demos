/*
author:
sources:
description:
*/

#include "rbtree.h"
#include <iostream>
#include <iomanip>

// GLOBALS


///////////////////////////////////////
//constructor/destructors

rbTree::rbTree() {
	//create sentinel which always has black color
	nil = new node;
	nil->color = 'b';
	nil->key = 101010101;
	//set root to sentinel, which we use in place of 'NULL'
	root = nil;
}

rbTree::~rbTree() {
	destroyTree(root);
	delete nil;
}

//////////////////////////////////////
// maintinence funcs

// recursively destroy tree
void rbTree::destroyTree(node *& tempNode) {
	//only execute when root, or any node, is not sentinel
	if (tempNode != nil) {
		destroyTree(tempNode->left);
		destroyTree(tempNode->right);
		delete tempNode;
	}
}

//////////////////////////////////////
// project requirements

// insert by integer
void rbTree::insert(int x) {
	node * cur = new node;
	cur->parent = nil;
	cur->left = nil;
	cur->right = nil;
	cur->key = x;
	cur->color = 'r';
	node * prev = nil;
	node * next = root;
	
	//if there is a root, find position for cur using 'prev'
	while (next != nil) {
		prev = next;
		if (cur->key < next->key)
			next = next->left;
		else
			next = next->right;
	}
	//if no root, make
	if (prev == nil)
		root = cur;
	//if key is less than position determined (prev) in while loop, place, else
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

// fix by balancing tree using red-black node properties
// note: no restriction on black nodes neighbors
void rbTree::insertFix(node * cur) {
	//while parent red (which violates property 4)
	while (cur->parent->color == 'r') {
		//if parent leftchild, select uncle
		node * other = cur->parent->parent->right;
		if (cur->parent == cur->parent->parent->left) {
			other = cur->parent->parent->right;
			//if uncle is red, change parent and uncle to black, grandp to red
			//and exchange cur and grandparent (case 1)
			if (other->color == 'r') {
				cur->parent->color = 'b';
				other->color = 'b';
				cur->parent->parent->color = 'r';
				cur = cur->parent->parent;
			}
			//if cur is rightchild, double rotate
			else if (cur == cur->parent->right) {
				//case 2, we know uncle black
				cur = cur->parent;
				leftRotate(cur);
				//case 3, cur and parent red
				cur->parent->color = 'b';
				cur->parent->parent->color = 'r';
				rightRotate(cur->parent->parent);
			}
		}
		//same as if but reversed tree side
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
	//always set root to black
	root->color = 'b';		
}


//remove
void rbTree::remove(int x) {
	//first we find node to remove
	node * cur = findNodeByKey(x);
	//cout << "curkey is: " << cur->key << endl;
	//cout << "cur: " << cur->parent << endl;	
	
	//new node from node to be removed
	//keep original color
	
	//set temp to node when cur has < 2 children
	node * temp = cur;
	char tempOrigColor = temp->color;
	if (cur->left == nil) {
		node * temp2 = cur->right;
		transplant(cur, cur->right);
	}
	else if (cur->right == nil) {
		node * temp2 = cur->left;
		transplant(cur, cur->left);
	}
	else {
		temp = findMinNode(cur->right);
		tempOrigColor = temp->color;
		node * temp2 = temp->right;
		if (temp->parent == cur)
			temp2->parent = temp;
		else {
			transplant(temp, temp->right);
			temp->right = cur->right;
			temp->right->parent = temp;
		}
		transplant(cur, temp);
		temp->left = cur->left;
		temp->left->parent = temp;
		temp->color = cur->color;
	}
	if (tempOrigColor == 'b')
		cout << "done" << endl;
		//deletefixupho

}


//removefix
void rbTree::removeFix(node * cur) {

}

// return largest key in tree
int rbTree::maximum() {
	node * cur = findMaxNode(root);
	return cur->key;
}

// return smallest key in tree
int rbTree::minimum() {
	node * cur = findMinNode(root);
	return cur->key;
}

//////////////////////////////////////////////////////////////
// node movement/maintinence functions

// find node of minimum
node* rbTree::findMinNode(node * cur) {
	while (cur->left != nil)
		cur = cur->left;
	return cur;
}

node* rbTree::findMaxNode(node * cur) {
	while (cur->right != nil)
		cur = cur->right;
	return cur;
}

// find node by key
node* rbTree::findNodeByKey(int x) {
	node * cur = root;
	while (cur != nil && x != cur->key) {
		if (x < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return cur;
}

// find successor
node* rbTree::findSuccessor(node * cur) {
	if (cur->right != nil) {
		while (cur->left != nil)
			cur = cur->left;
		return cur;
	}
	node * other = cur->parent;
	while (other != nil && cur == other->right) {
		cur = other;
		other = other->parent;
	}
	return other;
}


// transplant, used to move subtrees(by moving their roots)
void rbTree::transplant(node * cur, node * toMove) {

	if (cur->parent == nil)
		root = toMove;
	else if (cur == cur->parent->left)
		cur->parent->left = toMove;
	else
		cur->parent->right = toMove;
	toMove->parent = cur->parent;
}

// left rotate 
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

// right rotate
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


///////////////////////////////////////////////////////////
//print function
void rbTree::print() {
	inOrderPrint(root);
	cout << "root: " << root->key << " color: " << root->color << endl;
}

void rbTree::inOrderPrint(node * cur) {
	if (cur == nil)
		return;
	inOrderPrint(cur->left);
	cout << "key: "<< cur->key << " color: " << cur->color << endl;
	inOrderPrint(cur->right);
}
