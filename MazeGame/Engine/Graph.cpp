#include "Graph.hpp"


Vertex::Vertex(int x, int y, int d)
{
	this->x = x;
	this->y = y;
	this->d = d;
}

void Vertex::addEdge(Vertex* V)
{
	Edges.push_back(V);
}

void Vertex::clear()
{
	while (!Edges.empty())
	{
		Edges.front()->clear();
		Edges.pop_front();
	}
}


void Graph::addEdge(Vertex *V)
{
	Edges.push_back(V);
}

void Graph::clear()
{
	while (!Edges.empty())
	{
		Edges.front()->clear();
		Edges.pop_front();
	}
}