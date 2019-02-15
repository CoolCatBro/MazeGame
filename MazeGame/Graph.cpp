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
	bool found = false;
	for (auto i = Edges.begin(); i != Edges.end(); i++)
	{
		if ( ((*i)->x == V->x) && ((*i)->y == V->y) )
		{
			(*i)->addEdge(V);
			found = true;
			break;
		}
	}
	if (!found)
	{
		Edges.push_back(V);
	}
}