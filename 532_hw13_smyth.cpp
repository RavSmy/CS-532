//  532_hw13_smyth.cpp
//  CS 542 - Discrete Structures
//  Homework #13

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<set>
#include<algorithm>
using namespace std; 

typedef int Vertex;
typedef std::set<Vertex> VertexSet;
typedef std::set<Vertex> Edge;
typedef std::set<Edge> EdgeSet;
typedef std::pair<VertexSet, EdgeSet> Graph;
typedef std::map<Vertex, VertexSet> Graph2;

void bfs(const Graph2 &g2, Vertex start);
void dfs(const Graph2 &g2, Vertex start);
Vertex bfsCheckChild(map<Vertex,int> distance, VertexSet vertices);
Vertex dfsCheckChild(map<Vertex,bool> visited, VertexSet vertices); 

ostream &operator<<(std::ostream &out, VertexSet &v) {
	VertexSet::iterator it;
	
	out << "{" << *v.begin() << ", " << *(++v.begin()) << "}";
	return out;
}

Graph2 graph2FromGraph(Graph &g) {
	Graph2 ret;
	for (const Vertex &v : g.first)
	{
		ret.insert(make_pair(v, VertexSet()));
	}
	for (const Edge &e : g.second)
	{
		vector<Vertex> vv;
		for (const Vertex &v : e)
		{
			vv.push_back(v);
		}
		ret[vv[0]].insert(vv[1]);
		ret[vv[1]].insert(vv[0]);
	}
	return ret;
}

int main() {
	Graph g1{ {1,2,3,4,5,6,7,8,9},{{1,3},{1,4},{1,5},{1,6},{2,3},{2,4},{3,5},{5,6},{7,8},{8,9}} };
	Graph2 g2 = graph2FromGraph(g1);

	bfs(g2, 3);
	dfs(g2, 3);
}

void bfs(const Graph2 &g2, Vertex start) {
	Graph2 graph = g2;
	map<Vertex,int> distance;
	queue <int> vertices;
	int holder; 

	for(auto it = graph.begin(); it != graph.end(); it++)
		distance[it->first] = -1;

	cout << "BFS:\n" << start << " " << 0 << "\n";
	distance[start] = 0;
	vertices.push(start);

	while(!vertices.empty()) {
		holder = bfsCheckChild(distance, graph[vertices.front()]);
		if (holder > -1) {
			distance[holder] = distance[vertices.front()] +1; 
			cout << holder << " " << distance[holder] <<"\n";
			vertices.push(holder);
		}		
		else
			vertices.pop();			
	}	
	
}

void dfs(const Graph2 &g2, Vertex start) {
	Graph2 graph = g2;
	stack <int> dfsResult;
	map<Vertex,bool> visited;
	int holder; 

	for(auto it = graph.begin(); it != graph.end(); it++)
		visited[it->first] = false;

	cout << "DFS:\n" << start << "\n";
	visited[start] = true;
	dfsResult.push(start);

	while(!dfsResult.empty()) {
		holder = dfsCheckChild(visited, graph[dfsResult.top()]);
		if (holder == -1) {
			dfsResult.pop(); 		
		}
		else {
			cout << holder << "\n";
			dfsResult.push(holder);
			visited[holder] = true;
		}
	}	

}

Vertex bfsCheckChild(map<Vertex,int> distance, VertexSet vertices) {
	for (Vertex i : vertices)
		if (distance[i] == -1)
			return i;
	return -1;
}

Vertex dfsCheckChild(map<Vertex,bool> visited, VertexSet vertices) {
	for (Vertex i : vertices)
		if (!visited[i])
			return i;
	return -1;
}


