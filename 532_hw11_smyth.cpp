//  532_hw11_smyth.cpp
//  CS 542 - Discrete Structures
//  Homework #11

//include "stdafx.h"
#include "iostream"
#include <set>

using namespace std;

typedef int Vertex;
typedef set<Vertex> VertexSet;
typedef set<Vertex> Edge; // size 2
typedef set<Edge> EdgeSet;
typedef pair<VertexSet, EdgeSet> Graph;

Graph createComplete(unsigned v);
bool isComplete(const Graph & g);
Graph createCycle(unsigned v);
bool isCycle(const Graph & g);
Graph createWheel(unsigned v);
bool isWheel(const Graph & g);
Graph createCompleteBipartite(unsigned v1, unsigned v2);
bool isCompleteBipartite(const Graph & g);

int main()
{
	if (isComplete(createComplete(4)))
	cout << isComplete(createComplete(4))
	
	     << isCycle(createCycle(4))
	
	     << isWheel(createWheel(5))
	   
	    <<isCompleteBipartite(createCompleteBipartite(2, 3));

}

Graph createComplete(unsigned v)
{
	VertexSet vs; EdgeSet es;

	for (int i = 0; i < v; i++) {
		vs.insert(i);
		for (int j = 0; j < v; j++) {
			if (j != i) {
				Edge temp = { i };
				temp.insert(j);
				es.insert(temp);
			}
		}
	}

	return Graph{ vs, es };
}
bool isComplete(const Graph & g)
{
	int count = 0;
	int largest = 0;

	for (auto it = g.first.begin(); it != g.first.end(); it++)
	{
		count++;
		if (*it != count)
			return false;

		if (largest < *it)
			largest = *it;
	}

	count = 0;

	for (auto it = g.second.begin(); it != g.second.end(); it++)
	{
		for (auto its = it->begin(); its != it->end(); its++)
		{
			count++;
		}
	}
	count = count / 2;
	if (((largest *(largest - 1))) / 2 != count)
	{
		return false;
	}
	return true;
}
Graph createCycle(unsigned v)
{
	VertexSet vs; EdgeSet es;

	for (int i = 0; i < v; i++) {
		vs.insert(i);
		Edge temp = { i };
		if (i == v - 1) temp.insert(0);
		else temp.insert(i + 1);
		es.insert(temp);
	}

	return Graph{ vs, es };
}
bool isCycle(const Graph & g)
{
	int bcount = 0;
	for (auto it = g.first.begin(); it != g.first.end(); it++)
	{
		bcount++;
		if (*it != bcount)
			return false;
	}

	int count = 1;
	int tcount = 0;
	bool pass = false;
	for (auto it = g.second.begin(); it != g.second.end(); it++)
	{
		if (pass == true)
			count++;
		tcount = count;
		for (auto its = it->begin(); its != it->end(); its++)
		{
			if (*its != bcount)
			{
				if (*its != tcount)
					return false;

				tcount++;
			}
			else
			{
				pass = true;
			}
		}
	}
	count++;
	if (count != bcount)
		return false;

	return true;
}
Graph createWheel(unsigned v)
{
	Graph g = createCycle(v - 1);
	g.first.insert(v - 1);
	for (int i = 0; i < v - 1; i++)
		g.second.insert(Edge{ int(v) - 1, i });
	return g;
}
bool isWheel(const Graph & g)
{
	bool everyOther = false;
	int v = 0;
	for (auto it = g.first.begin(); it != g.first.end(); it++)
	{
		v++;
		if (*it != v)
			return false;
	}
	bool swch = true;
	int count = 1,
		tcount = 2,
		fLim = 3;
	for (auto it = g.second.begin(); it != g.second.end(); it++)
	{
		if (count == 1)
		{
			for (auto its = it->begin(); its != it->end(); its++)
			{
				if (*its != 1)
				{
					if (*its != tcount)
					{
						return false;
					}
					else if (*its == 2)
					{
						tcount = v - 1;
					}
					else if (*its == v - 1)
					{
						tcount = v;
					}
					else if (*its == v)
					{
						count = 2;
					}
				}
			}
		}
		else if (count != v - 1)
		{
			tcount = count;

			if (swch)
			{
				for (auto its = it->begin(); its != it->end(); its++)
				{
					if (*its != tcount)
						return false;

					tcount++;
				}
				swch = false;
			}
			else
			{
				for (auto its = it->begin(); its != it->end(); its++)
				{

					if (*its != v && *its != count)
						return false;

					tcount++;
				}
				swch = true;
				count++;

			}
		}
		else
		{
			tcount = v - 1;
			for (auto its = it->begin(); its != it->end(); its++)
			{
				if (*its != tcount)
					return false;

				tcount++;
			}
		}
	}
	return true;
}
Graph createCompleteBipartite(unsigned v1, unsigned v2)
{
	VertexSet vs; EdgeSet es;

	for (int i = 0; i < v1; i++) {
		vs.insert(i);
		for (int j = v1; j < v2 + v1; j++) {
			if (i == 0) vs.insert(j);
			Edge temp = { i };
			temp.insert(j);
			es.insert(temp);
		}
	}

	return Graph{ vs, es };
}
bool isCompleteBipartite(const Graph & g)
{

	int largest = 0;
	int count = 0,
		v1, v2;
	for (auto it = g.first.begin(); it != g.first.end(); it++)
	{
		count++;
		if (*it != count)
			return false;
		if (largest < *it)
			largest = *it;
	}
	auto itr = g.second.begin();
	auto itrs = itr->begin();
	itrs++;
	bool swch = true;
	v1 = *itrs - 1;
	v2 = largest - v1;
	v1 = 1;
	int c = v1,
		cs = v2;
	for (auto it = g.second.begin(); it != g.second.end(); it++)
	{
		for (auto its = it->begin(); its != it->end(); its++)
		{
			if (swch)
			{
				swch = false;
				if (*its != c)
					return false;
			}
			else
			{
				if (*its != cs)
					return false;
				else
				{
					cs++;
					swch = true;
					if (cs > largest)
					{
						cs = v2;
						c++;
					}
				}
			}
		}

	}

	return true;
}
