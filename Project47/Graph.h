#pragma once
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

class Graph {

private:
	int V;
	set<int>* edges; //array of set - type int

public:

	//constructors
	Graph();
	Graph(int V);
	Graph(const Graph& other);
	Graph& operator= (const Graph& other);

	//distructor
	~Graph();


	//functions
	int addEdge(int sour,int dest);
	void print_graph();
	int* BFS(int startVertex) const;
	int getV() const;
	set<int>& getAdjList(int vertex) const;
};