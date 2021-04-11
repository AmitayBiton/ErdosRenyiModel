#include "Graph.h"
#include <iostream>
#include <random>
#include <math.h>  

using namespace std;
//function decleration

bool random_bool_with_prob(double);
Graph build_random_graph(int, double);
int connectivity(Graph);
int diameter(Graph);
int is_isolated(Graph);
double threshold1and3(Graph);
double threshold2(Graph);
int firstHabitApplies(Graph, double);
int secondHabitApplies(Graph, double);
int thirdHabitApplies(Graph, double);


//random
std::knuth_b rand_engine;
std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);


void main() {
	
	/*
	first habit - graph with 1000 vertex:

	              ln(V)     ln(1000)
	threshold1 = ------- = ---------- = 0.00690776
	               V          1000
	
	*/
	
	double* firstHabitPList = new double[10];
	firstHabitPList[0] = 0.004;
	firstHabitPList[1] = 0.0045;
	firstHabitPList[2] = 0.005;
	firstHabitPList[3] = 0.0055;
	firstHabitPList[4] = 0.006;
	firstHabitPList[5] = 0.0075;
	firstHabitPList[6] = 0.008;
	firstHabitPList[7] = 0.0085;
	firstHabitPList[8] = 0.009;
	firstHabitPList[9] = 0.0095;
	
	/*
	TODO:
	foreach p in firstHabitPList genetate 500 graphs and detemine how many of them applies to habit 1

	*/



	/*
	second habit - graph with 1000 vertex:
				   _________
				  |  2ln(V)     
	threshold2 =  | -------   = 0.117539
				 \|    V         

	*/
	double* secondHabitPList = new double[10];
	secondHabitPList[0] = 0.075;
	secondHabitPList[1] = 0.08;
	secondHabitPList[2] = 0.085;
	secondHabitPList[3] = 0.09;
	secondHabitPList[4] = 0.1;
	secondHabitPList[5] = 0.2;
	secondHabitPList[6] = 0.25;
	secondHabitPList[7] = 0.3;
	secondHabitPList[8] = 0.35;
	secondHabitPList[9] = 0.4;

	/*
	TODO:
	foreach p in secondHabitPList genetate 500 graphs and detemine how many of them applies to habit 2

	*/


	/*
	third habit - graph with 1000 vertex:

				  ln(V)     ln(1000)
	threshold1 = ------- = ---------- = 0.00690776
				   V          1000
	*/

	double* thirdHabitPList = new double[10];
	thirdHabitPList[0] = 0.004;
	thirdHabitPList[1] = 0.0045;
	thirdHabitPList[2] = 0.005;
	thirdHabitPList[3] = 0.0055;
	thirdHabitPList[4] = 0.006;
	thirdHabitPList[5] = 0.0075;
	thirdHabitPList[6] = 0.008;
	thirdHabitPList[7] = 0.0085;
	thirdHabitPList[8] = 0.009;
	thirdHabitPList[9] = 0.0095;

	/*
	TODO:
	foreach p in thirdHabitPList genetate 500 graphs and detemine how many of them applies to habit 3

	*/



	Graph g = build_random_graph(1000, 0.1);
	Graph g2 = build_random_graph(1000, 0.25);

	//g.print_graph();
	//cout << endl << endl;
	//g2.print_graph();
	
	double t1 = threshold1and3(g);
	double t2 = threshold2(g);
	cout << "threshold1 = ( ln(V)/V ) = " << t1 << endl;
	cout << "threshold2 = ( sqrt(2*ln(V)/V) ) = " << t2 << endl;

	cout << endl;
	cout << "first habit applies to 'g' ? : " << firstHabitApplies(g, 0.1) << endl;
	cout << "first habit applies to 'g2' ? : " << firstHabitApplies(g2, (double)0.25) << endl;
	cout << endl;
	cout << "second habit applies to 'g' ? : " << secondHabitApplies(g, 0.1) << endl;
	cout << "second habit applies to 'g2' ? : " << secondHabitApplies(g2, (double)0.25) << endl;
	cout << endl;
	cout << "third habit applies to 'g' ? : " << thirdHabitApplies(g, 0.1) << endl;
	cout << "third habit applies to 'g2' ? : " << thirdHabitApplies(g2, (double)0.25) << endl;


	//cout << "Connectivity1: " << connectivity(g) << endl;
	//cout << "Diameter1: " << diameter(g) << endl;
	//cout << "Is isolated1: " << is_isolated(g) << endl;
	//cout << "Connectivity2: " << connectivity(g2) << endl;
	//cout << "Diameter2: " << diameter(g2) << endl;
	//cout << "Is isolated2: " << is_isolated(g2) << endl;
}



//rand false/true for the prob
bool random_bool_with_prob(double prob)
{
	return uniform_zero_to_one(rand_engine) < prob;
}


//build random graph
Graph build_random_graph(int v, double p) {
	Graph g(v);
	for (int i = 0; i < v; i++)
	{
		for (int j = i + 1; j < v; j++)
		{
			if (random_bool_with_prob(p)) {
				//cout << "Adding Edge: (" << i << ", " << j << ")" << endl;
				g.addEdge(i, j);
			}
		}
	}
	return g;
}


//checks ig g is connected
int connectivity(Graph g) {
	int* distances = g.BFS(0);
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return 0;
	}
	return 1;
}


//gind g diameter
int diameter(Graph g) {
	int* distances = g.BFS(0);
	int maxd = 0, farrestV = 0;
	// finding first end of the diameter
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return -1; // Not connected Graph
		if (distances[i] > maxd) {
			maxd = distances[i];
			farrestV = i;
		}
	}
	//cout << farrestV << "<->";
	distances = g.BFS(farrestV);
	maxd = 0;
	// finding second end of the diameter
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] > maxd) {
			maxd = distances[i];
			farrestV = i;
		}
	}

	//cout << farrestV << endl;
	return maxd;
}


//checks if there is v without adj
int is_isolated(Graph g) {
	for (int i = 0; i < g.getV(); i++)
	{
		if (g.getAdjList(i).empty())
			return 1;
	}
	return 0;
}


//calculate thresholds:
double threshold1and3(Graph g)
{
	/*
	              ln(V)
	threshold1 = -------
	                V
	*/

	double V = (double)g.getV();
	return (log(V) / V);
}
double threshold2(Graph g)
{
	/*
				   _________
				  |  2ln(V)
	threshold2 =  | -------   
				 \|    V
	*/

	double V = (double)g.getV();
	return sqrt((2 * log(V)) / V);
}


//checkHabits
int firstHabitApplies(Graph g,double p) {
	int isConnective = connectivity(g);
	double thresh1 = threshold1and3(g);
	if (( p > thresh1 && isConnective == 1 ) || ( p < thresh1 && isConnective == 0 ))
	{
		return 1;
	}
	return 0;
}
int secondHabitApplies(Graph g, double p) 
{
	
	int diam = diameter(g);
	double thresh2 = threshold2(g);

	if (( p > thresh2 && diam == 2 ) || (p < thresh2 && diam > 2))
	{
		return 1;
	}
	return 0;
}
int thirdHabitApplies(Graph g, double p)
{
	int hasLonely = is_isolated(g);
	double thresh3 = threshold1and3(g);

	if (( p < thresh3 && hasLonely ==1 ) || ( p > thresh3 && hasLonely == 0 ))
	{
		return 1;
	}
	return 0;
}

