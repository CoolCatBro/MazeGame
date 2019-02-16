#include "Graph.hpp"

Vertex::Vertex(int x, int y, int d = 0)
{
	this->x = x;
	this->y = y;
	this->d = d;
}

void Vertex::addEdge(Vertex* V)
{
	Edges.push_back(V);
}

void Graph::addEdge(Vertex *V)
{
	Edges.push_back(V);
}