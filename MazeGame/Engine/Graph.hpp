#pragma once

#include <list>

using std::list;

class Vertex
{
public:

	int x,y,d;
	list<Vertex*> Edges;


	Vertex(int x, int y, int d=0);

	void clear();
	void addEdge(Vertex* V);
};

class Graph
{
public:

	list<Vertex*> Edges;
	
	void addEdge(Vertex* V);
	void clear();
};

