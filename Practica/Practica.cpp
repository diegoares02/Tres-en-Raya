// Practica.cpp: define el punto de entrada de la aplicación de consola.
//Aplicacion que demuestra la implementacion del metodo de busqueda por anchura

#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

// Node class
class Node {
	int key;
	Node* left;
	Node* right;
public:
	Node() { key = -1; left = NULL; right = NULL; };//Constructor
	//Popiedades
	void setKey(int aKey) { key = aKey; };
	void setLeft(Node* aLeft) { left = aLeft; };
	void setRight(Node* aRight) { right = aRight; };
	int Key() { return key; };
	Node* Left() { return left; };
	Node* Right() { return right; };
};

// Tree class
class Tree {
	Node* root;
public:
	Tree();
	~Tree();
	Node* Root() { return root; };
	void addNode(int key);
	void levelOrder(Node* n);
private:
	void addNode(int key, Node* leaf);
	void freeNode(Node* leaf);
};

// Constructor
Tree::Tree() {
	root = NULL;
}

// Destructor
Tree::~Tree() {
	freeNode(root);
}

// Free the node
void Tree::freeNode(Node* leaf)
{
	if (leaf != NULL)
	{
		freeNode(leaf->Left());
		freeNode(leaf->Right());
		delete leaf;
	}
}

// Add a node
void Tree::addNode(int key) {
	// No elements. Add the root
	if (root == NULL) {
		cout << "add root node ... " << key << endl;
		Node* n = new Node();
		n->setKey(key);
		root = n;
	}
	else {
		cout << "add other node ... " << key << endl;
		addNode(key, root);
	}
}

// Add a node (private)
void Tree::addNode(int key, Node* leaf) {
	if (key <= leaf->Key()) {
		if (leaf->Left() != NULL)
			addNode(key, leaf->Left());
		else {
			Node* n = new Node();
			n->setKey(key);
			leaf->setLeft(n);
		}
	}
	else {
		if (leaf->Right() != NULL)
			addNode(key, leaf->Right());
		else {
			Node* n = new Node();
			n->setKey(key);
			leaf->setRight(n);
		}
	}
}

// Print the tree level-order assisted by queue
void Tree::levelOrder(Node* n) {
	// Create a queue
	queue<Node*> q;

	// Push the root
	q.push(n);

	while (!q.empty())
	{
		// Dequeue a node from front
		Node* v = q.front();
		cout << v->Key() << " ";

		// Enqueue the left children
		if (v->Left() != NULL)
			q.push(v->Left());

		// Enqueue the right children
		if (v->Right() != NULL)
			q.push(v->Right());

		// Pop the visited node
		q.pop();
	}
}

// Test main program
int main() {
	Tree* tree = new Tree();
	int aux=0,orden;
	cout << "Ingrese el nivel: " << endl;
	cin >> orden;
	for (int i = 0; i < (pow(2,orden)-1); i++)
	{
		cout << "Ingrese el valor: "; cin >> aux;
		tree->addNode(aux);
	}
	cout << "Level order traversal" << endl;
	tree->levelOrder(tree->Root());
	cout << endl;

	delete tree;
	system("pause");
}