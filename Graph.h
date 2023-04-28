#pragma once
#include "jak_dojade.cpp"
// This class represents a directed graph using
// adjacency list representation
class Graph {

	// No. of vertices
	int V;

	// Pointer to an array containing adjacency lists
	vector<list<int> > adj;

public:
	// Constructor
	Graph(int V);

	// Function to add an edge to graph
	void addEdge(int v, int w);

	// Prints BFS traversal from a given source s
	void BFS(int s);
};
