#include "Graph.h"
#include <queue>

//constructors 

Graph::Graph() {
	this->V = 0;
	//initialization the array
	edges = NULL;
}

Graph::Graph(int V) {
	this->V = V;
	//initialization the array
	edges = new set<int> [V];
}

//copy constructor
Graph::Graph(const Graph& other) {
	edges = NULL;
	*this = other;
}


Graph& Graph::operator= (const Graph& other) {
	//delete if not NULL
	if (this != &other) {
		if (edges != NULL) {
			delete[] edges;
		}

		V = other.V;
		edges = new set<int> [V];
		for (int i = 0; i < V; i++)
		{
			edges[i] = other.edges[i];
		}
	}
	return *this;
}

//distructor

Graph::~Graph() {
	if (edges != NULL) {
		delete[] edges;
	}
}

//functions

int Graph::addEdge(int sour, int dest) {

	if (sour<0 || sour>V || dest<0 || dest>V)
		return 0;
	//adding edges of the grapgh
	edges[sour].insert(dest);
	edges[dest].insert(sour);
	return 1;
}

void Graph::print_graph() {
	if (edges != NULL) {
		for (int i = 0; i < V; i++)
		{
			cout << "Node " << i << ": ";
			for_each(edges[i].begin(), edges[i].end(), [](int dst) {cout << dst << ", "; });
			cout << endl;
		}
	}
}

int Graph::getV() const {
	return V;
}

set<int>& Graph::getAdjList(int vertex) const {
	return edges[vertex];
}

// BFS algorithm
int* Graph::BFS(int startVertex) const{
	int* distances = new int[V];
	for (int i = 0; i < V; i++)
		distances[i] = -1;

	queue<int> q;

	distances[startVertex] = 0;
	q.push(startVertex);

	set<int>::iterator i;

	while (!q.empty()) {
		int currVertex = q.front();
		//cout << "Visited " << currVertex << " ";
		q.pop();

		for (i = edges[currVertex].begin(); i != edges[currVertex].end(); ++i) {
			int adjVertex = *i;
			if (distances[adjVertex] == -1) {
				distances[adjVertex] = distances[currVertex] + 1;
				q.push(adjVertex);
			}
		}
	}

	return distances;
}