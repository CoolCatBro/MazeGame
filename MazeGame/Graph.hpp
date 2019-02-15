#pragma once

#include <list>

using std::list;

class Vertex
{
public:

	int x,y,d;
	list<Vertex*> Edges;

	Vertex(int x, int y, int d);

	void addEdge(Vertex* V);
};

class Graph
{
public:

	list<Vertex*> Edges;
	
	void addEdge(Vertex* V);
};

