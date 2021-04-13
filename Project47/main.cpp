#include "Graph.h"
#include <iostream>
#include <random>
#include <math.h>  
#include <fstream>

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
void exportResultToCsv(double* , double* , string );

//random
std::knuth_b rand_engine;
std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);


void main() {
	
	cout << "generating graphs and validates habits"<<endl;
	int numberOfSamples = 500;
	cout << "number of sumples: " << numberOfSamples << endl;

	/*
	first habit - graph with 1000 vertex:

				  ln(V)     ln(1000)
	threshold1 = ------- = ---------- = 0.00690776
				   V          1000

	*/
	
	cout << "-------------------------------------------------" << endl;
	cout << "                working on habit 1               " << endl;
	cout << "-------------------------------------------------" << endl;

	double firstHabitPList[] = { 0.004 ,0.0045 ,0.005 ,0.0055 ,0.006 ,0.0075 ,0.008 ,0.0085 ,0.009 ,0.0095 };
	double* firstHabitResults = new double[10];
	

	for (int p = 0; p < 10; p++) 
	{
		cout << endl << endl << "Probability: " << firstHabitPList[p] << endl;
		double countOfFirst = 0;
		//cout << "generating graphs with probability: " << firstHabitPList[p] << endl;
		for (int i = 0; i < numberOfSamples; i++)
		{	
			cout << "Progress: " << i+1 << "/" << numberOfSamples << "\r";
			Graph g = build_random_graph(1000, firstHabitPList[p]);
			if(firstHabitApplies(g, firstHabitPList[p]) == 1)
			{
				countOfFirst++;
			}
			
		}
		firstHabitResults[p] = countOfFirst/numberOfSamples;
	}
	cout << endl << endl << "exporting to file..." << endl;
	exportResultToCsv(firstHabitPList, firstHabitResults, "habit1Results.csv");
	cout << "Done." << endl;

	/*
	second habit - graph with 1000 vertex:
				   _________
				  |  2ln(V)     
	threshold2 =  | -------   = 0.117539
				 \|    V         

	*/


	cout << "-------------------------------------------------" << endl;
	cout << "                working on habit 2               " << endl;
	cout << "-------------------------------------------------" << endl;
	double secondHabitPList[] = { 0.075 ,0.08 ,0.085 ,0.09 ,0.1 ,0.2 ,0.25 ,0.3 ,0.35 ,0.4 };
	double* secondHabitResults = new double[10];
	
	for (int p = 0; p < 10; p++)
	{
		cout << endl << endl << "Probability: " << firstHabitPList[p] << endl;
		double countOfSecond = 0;
		//cout << "generating graphs with probability: " << secondHabitPList[p] << endl;
		for (int i = 0; i < numberOfSamples; i++)
		{
			cout << "Progress: " << i + 1 << "/" << numberOfSamples << "\r";
			Graph g = build_random_graph(1000, secondHabitPList[p]);
			if (secondHabitApplies(g, secondHabitPList[p]) == 1)
			{
				countOfSecond++;
			}
		}
		secondHabitResults[p] = countOfSecond / numberOfSamples;
	}
	cout << endl << endl << "exporting to file..." << endl;
	exportResultToCsv(secondHabitPList, secondHabitResults, "habit2Results.csv");
	cout << "Done." << endl;



	/*
	third habit - graph with 1000 vertex:

				  ln(V)     ln(1000)
	threshold1 = ------- = ---------- = 0.00690776
				   V          1000
	*/

	cout << "-------------------------------------------------" << endl;
	cout << "                working on habit 3               " << endl;
	cout << "-------------------------------------------------" << endl;

	double thirdHabitPList[] = { 0.004 ,0.0045 ,0.005 ,0.0055 ,0.006 ,0.0075 ,0.008 ,0.0085 ,0.009 ,0.0095 };
	double* thirdHabitResults = new double[10];

	for (int p = 0; p < 10; p++)
	{
		cout << endl << endl << "Probability: " << firstHabitPList[p] << endl;
		double countOfthird = 0;
		//cout << "generating graphs with probability: " << thirdHabitPList[p] << endl;
		for (int i = 0; i < numberOfSamples; i++)
		{
			cout << "Progress: " << i + 1 << "/" << numberOfSamples << "\r";
			Graph g = build_random_graph(1000, thirdHabitPList[p]);
			if (secondHabitApplies(g, thirdHabitPList[p]) == 1)
			{
				countOfthird++;
			}

		}
		thirdHabitResults[p] = countOfthird / numberOfSamples;
	}
	cout << endl << endl << "exporting to file..." << endl;
	exportResultToCsv(thirdHabitPList, thirdHabitResults, "habit3Results.csv");
	cout << "Done." << endl;

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


void exportResultToCsv(double* Plist, double* results, string filename)
{
	ofstream Habit1File(filename);
	Habit1File << "P,";
	for (int p = 0; p < 9; p++)
	{
		Habit1File << Plist[p] << ",";
	}
	Habit1File << Plist[9] << endl;

	Habit1File << "ApplicationCount,";
	for (int p = 0; p < 9; p++)
	{
		Habit1File << results[p] << ",";
	}
	Habit1File << results[9] << endl;

	Habit1File.close();
}