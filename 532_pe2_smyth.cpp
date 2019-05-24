//  532_pe2_smyth.cpp
//  CS 542 - Discrete Structures
//  Practice Exam Prob #2

#include <algorithm>  
#include <iostream>
#include <map>
#include <set>
#include <vector> 
using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet; 
typedef map<Vertex, VertexSet> Graph2;


vector<Vertex> vectorFromSet(const VertexSet & vs) 
{ 
	vector<Vertex> ret;    
	for (const Vertex & v : vs)        
		ret.push_back(v);    
	return ret; 
}

Graph2 cycle(unsigned vertices);
bool isCycle(const Graph2 & g2);
void show(const Graph2 & g2);

int main()
{
	cout << isCycle(Graph2 { { 4,{4} },{ 9,{ 9 } }, { 2,{ 2 } }, { 5,{ 5 } } })
		 << isCycle(Graph2{ { 4,{ 5,2 } },{ 9,{ 5 } },{ 2,{ 9 } },{ 5,{ 4 } } })
		 << isCycle(Graph2{ { 4,{ 9 } },{ 9,{ 4 } },{ 2,{ 5 } },{ 5,{ 2 } } })
		 << isCycle(Graph2{ { 4,{ 2 } },{ 9,{ 5 } },{ 2,{ 9 } },{ 5,{ 4 } } })
		 << isCycle(cycle(100));	
}


Graph2 cycle(unsigned vertices) {
	Graph2 cycleG;

	for (Vertex i = 1; i <= vertices; i++) 
		if (i != vertices)
			cycleG[i] = VertexSet{i+1};
		else
			cycleG[i] = VertexSet{1};

	return cycleG;
}

bool isCycle(const Graph2 & g2) {
	map<Vertex, bool> edgeFlag;

	// First check if .second points loops to .first || .second has more than one vertex
	// Mark .first vertex as exist, Mark .second vertex as accessed (as long as there's only one) 
	for (auto i = g2.begin(); i != g2.end(); ++i) {
		if (i->second.size() != 1 || (*(g2.find(*(i->second.begin()))->second.begin()) == i->first)) return false;

		if (edgeFlag.find(i->first) != edgeFlag.end() && (edgeFlag[i->first] != true)) edgeFlag[i->first] = false;

		if ((*(i->second.begin()) != i->first) && !edgeFlag[*(i->second.begin())])  edgeFlag[*(i->second.begin())] = true;
		else return false;

	}

	// Check all vertex have been accessed
	for (auto i = edgeFlag.begin(); i != edgeFlag.end(); ++i) 
		if (i->second == false) return false;
	

	return true;
}


void show(const Graph2 & g2) {

	for (auto it = g2.begin(); it != g2.end(); it++)
	{ 
		cout << "(" << it->first << ", {"; 

		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{ 
			if (it2 != it->second.begin())                
				cout << ", ";   

			cout << *it2; 
		}     

		cout << "})\n"; 
	} 

}

