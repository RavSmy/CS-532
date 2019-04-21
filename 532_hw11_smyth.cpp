//  532_hw10_smyth.cpp
//  CS 542 - Discrete Structures
//  Homework #10

#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef set<Vertex> Edge; // size 2
typedef set<Edge> EdgeSet;
typedef pair<VertexSet, EdgeSet> Graph;

Graph createComplete(unsigned v);
bool isComplete(const Graph & g); // check size first, then individ.
Graph createCycle(unsigned v);
bool isCycle(const Graph & g);
Graph createWheel(unsigned v);
Graph createCompleteBipartite(unsigned v1, unsigned v2);
void show(const Graph & g);
void show(const Edge & e);

int main() {

cout << isComplete(createComplete(5));

show(createCompleteBipartite(2,3));
	
}

Graph createComplete(unsigned v) {
	VertexSet vs; EdgeSet es; 

	for (int i =0; i < v; i++) {
		vs.insert(i);
		for (int j = 0 ; j < v; j++) {
			if (j != i) {
			Edge temp = {i};
			temp.insert(j);
			es.insert(temp);}
		} 	
	}
		
	return Graph {vs, es};
}

bool isComplete(const Graph & g) {
	Graph testG = createComplete(g.first.size());
	if (g.second == testG.second) return true;
	return false; 
}

Graph createCycle(unsigned v) {
	VertexSet vs; EdgeSet es; 

	for (int i =0; i < v; i++) {
		vs.insert(i);
		Edge temp = {i};
		if (i == v-1) temp.insert(0);
		else temp.insert(i+1);
		es.insert(temp);	
	}
		
	return Graph {vs, es};
}

bool isCycle(const Graph & g) {
	Graph testG = createCycle(g.first.size());
	if (g.second == testG.second) return true;
	return false; 
}

Graph createWheel(unsigned v) {
	Graph g = createCycle(v-1);
	g.first.insert(v-1);
	for (int i =0; i < v-1; i++)
		g.second.insert(Edge {v-1, i});
	return g;
}

bool isWheel(const Graph & g) {
	Graph testG = createWheel(g.first.size());
	if (g.second == testG.second) return true;
	return false; 
}

Graph createCompleteBipartite(unsigned v1, unsigned v2) {
	VertexSet vs; EdgeSet es; 

	for (int i =0; i < v1; i++) {
		vs.insert(i);
		for (int j = v1 ; j < v2+v1; j++) {
			if (i==0) vs.insert(j);
			Edge temp = {i};
			temp.insert(j);
			es.insert(temp);
		}		
	}
		
	return Graph {vs, es};
}

void show(const Graph & g){
	cout <<"Vertex set:";
	for(const Vertex & v: g.first)
		cout <<"  " <<v;
	cout <<endl;
	cout <<"Edge set:";
	for(const Edge & e: g.second){
		cout <<",  "; show(e);}
	cout <<endl;
}

void show(const Edge & e){ 
	for(const Vertex & v: e)
		cout <<"  " <<v;
}


