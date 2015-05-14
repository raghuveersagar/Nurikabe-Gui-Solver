#ifndef _PUZZLE_H
#define _PUZZLE_H

/*
* Puzzle.h
*
*  Created on: Nov 24, 2013
*      Author: Raghuveer Sagar
*/

#include<vector>

typedef std::pair<int, int> Pair;

/*Node class used to represent vertices of the graph.
* It has a pointer to the parent plus present configuration(data).
*
*/

template<class T>
class Node {
public:
	Node * parent;
	T nodeData;
public:

	Node(Node* n, T data) :
		parent(n), nodeData(data) {
	}

};

/*A representation of the Jug and its present state*/

/*This is the generic Puzzle Solver class can be used for all graph puzzles.
*
*Initialized with the starting node of the graph.
*
*/
template<class T>
class PuzzleSolver {

protected:
	Node<T> *startNode;
	//Node<T>* bfs(Node<T>*);

public:
	PuzzleSolver(T d) :
		startNode(new Node<T>(0, d)) {
	}
    T solve(); //implemented in base class
     //std::vector<Node<T>*> getConfigurations(Node<T>*) = 0; //implemented in derived class.Returns vector of possible nodes.
	virtual bool isRequiredConfiguration(T) = 0; //implemented in derived class.checks if the passed node is the node which is being searched.*/
	virtual void printFinalConfig(Node<T> * node) = 0; //print the configurations leading to the final node.

};


#endif

