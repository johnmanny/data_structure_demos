/*
author: John Nemeth
sources: class material, previous projects
description: implementation file for RBTree class
*/

#include "rbtree.h"
#include <iostream>
#include <iomanip>
#include <cstring>

///////////////////////////////////////
//constructor/destructors

rbTree::rbTree() {
	size = 0;
	//create sentinel which always has black color
	nil = new node;
	nil->color = 'b';
	nil->key = 1000001;
	nil->parent = nil;
	nil->left = nil;
	nil->right = nil;

	//set root to sentinel, which we use in place of 'NULL'
	root = nil;
}

rbTree::~rbTree() {
	destroyTree(root);
	delete nil;
}

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
	size++;
	node * cur = new node;
	cur->key = x;
	cur->left = nil;
	cur->right = nil;
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
	
	// use prev as insert point
	cur->parent = prev;
	if (prev == nil)
		root = cur;
	else if (cur->key < prev->key) {
		prev->left = cur;
	}
	else {
		prev->right = cur;
	}
	insertFix(cur);

}


/*
//////// INSERT FIX
	CASE A/B: parent is leftchild or rightchild
		case1: cur's uncle red
		case2: cur's uncle black and cur is right child
		case3: cur's uncle black and cur left child
*/
void rbTree::insertFix(node *& cur) {
	node * parent = nil;
	node * grandParent = nil;

	//while parent red (which violates property 4)
	while ((cur->parent->color == 'r') && (cur != root)) {
		parent = cur->parent;
		grandParent = cur->parent->parent;

		// case A
		// parent is a leftchild
		if (parent == grandParent->left) {
			node * uncle = grandParent->right;

			// case 1
			// uncle red, then only recolor
			if (uncle->color == 'r') {
				parent->color = 'b';
				uncle->color = 'b';
				grandParent->color = 'r';
				cur = grandParent;
			}
			else {

				// case 2
				// cur is rightchild, left rotation
				if (cur == parent->right) {
					//cur = cur->parent;
					//leftRotate(cur);
					leftRotate(parent);
					cur = parent;
					parent = cur->parent;
				}

				// case 3
				// cur is leftchild, right rotation req
				rightRotate(grandParent);
				parent->color = 'b';
				grandParent->color = 'r';
				cur = parent;
			}
		}
		// Case B
		// parent rightchild, reverse left and right operations, otherwise is same
		else {
			node * uncle = grandParent->left;

			if (uncle->color == 'r') {
				parent->color = 'b';
				uncle->color = 'b';
				grandParent->color = 'r';
				cur = grandParent;
			}
			else {
				 if (cur == parent->left) {
					rightRotate(parent);
					cur = parent;
				}
				leftRotate(grandParent);
				parent->color = 'b';
				grandParent->color = 'r';
				cur = parent;
			}
		}
	}
	//always set root to black
	root->color = 'b';		
}


/*////////////// REMOVE BY KEY
	want to delete node with key x. we find it and set it to toberemoved
	case1: toberemoved has < 2 children
		a. if no leftchild, transplant right subtree(could also be nil)
		b. elseif no rightchild, transplant left subtree(could also be nil)
	case2: toberemoved has 2 children
		a. find min node on right (successor, which has no left subtree)
		b. determine color of successor
		c. grab right subtree of successor
			1. if successor's parent is toberemoved(cur)
				
/////////////// COMMENTING IN PROGRESS */
bool rbTree::remove(int x) {
	
	// find node to remove
	node * toBeRemoved = findNodeByKey(x);
	if (toBeRemoved == nil)
		return false;
	node * successor = toBeRemoved;
	node * rightSubtree = NULL;
	char succOrigColor = successor->color;
	
	// Case 1 - A: no leftchild, so transplant right subtree 
	if (toBeRemoved->left == nil) {
		rightSubtree = toBeRemoved->right;
		transplant(toBeRemoved, toBeRemoved->right);
	}
	// Case 1 - B: no rightchild, so transplant left subtree 
	else if (toBeRemoved->right == nil) {
		rightSubtree = toBeRemoved->left;
		transplant(toBeRemoved, toBeRemoved->left);
	}
	// Case 2
	else {
		successor = findMinNode(toBeRemoved->right);	
		succOrigColor = successor->color;
		rightSubtree = successor->right;
		if (successor->parent == toBeRemoved)
			rightSubtree->parent = successor;
		else {
			transplant(successor, successor->right);
			successor->right = toBeRemoved->right;
			successor->right->parent = successor;
		}
		transplant(toBeRemoved, successor);
		successor->left = toBeRemoved->left;
		successor->left->parent = successor;
		successor->color = toBeRemoved->color;
	}
	// if original node color was black, removing it could've caused violations
	if (succOrigColor == 'b')
		removeFix(rightSubtree);
	delete toBeRemoved;
	size--;
	return true;
}


/*//////////// REMOVE FIX
	case1: cur's sibling red
	case2: cur's sibling temp is black, and both of temp's children black
	case3: cur's sibling black, temp's left red and right black
	case4: cur's sibling temp is black & temp's right is red */
void rbTree::removeFix(node *& cur) {
	while (cur != root && cur->color == 'b') {
		// if cur is left child, consider sibling (right child of parent)
		if (cur == cur->parent->left) {
			node * temp = cur->parent->right;
			if (temp->color == 'r') {
				temp->color == 'b';
				cur->parent->color == 'r';
				leftRotate(cur->parent);
				temp = cur->parent->right;
			}
			if (temp->left->color == 'b' && temp->right->color == 'b') {
				temp->color == 'r';
				cur = cur->parent;
			}
			else if (temp->right->color == 'b') {
				temp->left->color = 'b';
				temp->color = 'r';
				rightRotate(temp);
				temp = cur->parent->right;
			}
			temp->color = cur->parent->color;
			cur->parent->color = 'b';
			temp->right->color = 'b';
			leftRotate(cur->parent);
			cur = root;
		}
		// cur is right child
		else {
			node * temp = cur->parent->left;
			if (temp->color == 'r') {
				temp->color == 'b';
				cur->parent->color == 'r';
				rightRotate(cur->parent);
				temp = cur->parent->left;
			}
			if (temp->right->color == 'b' && temp->left->color == 'b') {
				temp->color == 'r';
				cur = cur->parent;
			}
			else if (temp->left->color == 'b') {
				temp->right->color = 'b';
				temp->color = 'r';
				leftRotate(temp);
				temp = cur->parent->left;
			}
			temp->color = cur->parent->color;
			cur->parent->color = 'b';
			temp->left->color = 'b';
			rightRotate(cur->parent);
			cur = root;
		}
	cur->color = 'b';
	}
}

// search for key (called from main)
bool rbTree::search(int key) {
	
	if (findNodeByKey(key) == nil)
		return false;
	else
		return true;
}

// return largest key in tree (called from main)
int rbTree::maximum() {
	node * cur = findMaxNode(root);
	if (cur == nil) {
		cout << "Empty" << endl;
		return 0;
	}
	else {
		cout << cur->key << endl;
		return cur->key;
	}
}

// return smallest key in tree (called from main)
int rbTree::minimum() {
	node * cur = findMinNode(root);
	if (cur == nil) {
		cout << "Empty" << endl;
		return false;
	}
	else {
		cout << cur->key << endl;
		return cur->key;
	}
}

//////////////////////////////////////////////////////////////
// node movement/maintinence functions

// find node of min key value
node* rbTree::findMinNode(node * cur) {
	while (cur->left != nil)
		cur = cur->left;
	return cur;
}

//find node with max keyvalue
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
	if (cur->key == x)
		return cur;
	else
		return nil;
}

// transplant, used to move subtrees(by moving their roots)
void rbTree::transplant(node *& cur, node *& toMove) {

	if (cur->parent == nil)
		root = toMove;
	else if (cur == cur->parent->left)
		cur->parent->left = toMove;
	else
		cur->parent->right = toMove;
	toMove->parent = cur->parent;
}

// left rotate 
void rbTree::leftRotate(node *& cur) {
	node * other = cur->right;	//set to rotate with
	cur->right = other->left;	//transplant subtrees
	if (other->left != nil)
		other->left->parent = cur;
	other->parent = cur->parent;	//link cur's parents to others
	if (cur->parent == nil)
		root = other;
	else if (cur == cur->parent->left)
		cur->parent->left = other;
	else 
		cur->parent->right = other;
	other->left = cur;		//place cur on other's left
	cur->parent = other;

}

// right rotate
void rbTree::rightRotate(node *& cur) {
	node * other = cur->left;	//set to rotate with
	cur->left = other->right;	//transplant subtrees
	if (other->right != nil)
		other->right->parent = cur;
	other->parent = cur->parent;	//link cur's parents to others
	if (cur->parent == nil)
		root = other;
	else if (cur == cur->parent->right)
		cur->parent->right = other;
	else 
		cur->parent->left = other;
	other->right = cur;		//place cur on other's left
	cur->parent = other;
}


///////////////////////////////////////////////////////////
//print function
void rbTree::print() {
	if (root == nil) {
		cout << "Empty" << endl;
		return;
	}
	else {
		int keys[size], index = 0;
		char spaces[size] = { ' ' };
		inOrderPrint(root, keys, index);
		for (index = 0; index < size; index++) {
			cout << keys[index];
			if (index < size - 1)
				cout << spaces[index];
		}	
	}
	cout << endl;

}

// original print function was recursive and O(lg n). altered for no whitespace
void rbTree::inOrderPrint(node * cur, int * keys, int & index) {
	if (cur == nil)
		return;
	inOrderPrint(cur->left, keys, index);
	keys[index] = cur->key;
	index++;
	inOrderPrint(cur->right, keys, index);
}
