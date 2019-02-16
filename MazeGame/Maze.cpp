#include "Maze.hpp"
#include <iostream>
using namespace std;

Maze::Maze(Scene* scene,int width, int height)
	 :Layer(scene,"maze"),width(width),height(height),dist(1,4)
{
	maze = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maze[i] = new int[width];
		for (int j = 0; j < width; j++)
			maze[i][j] = 1;
	}

	cell = new Cell(scene, width*height);

	rng.seed(std::random_device()());
}

void Maze::_createPath(Graph& graph,Vertex* V)
{
	if (maze[V->y][V->x])
	{
		graph.addEdge(V);
		maze[V->y][V->x] = 0;
	}

	if (_getNeighbour(V, 1) || _getNeighbour(V, 2) || _getNeighbour(V, 3) || _getNeighbour(V, 4))
	{
		int t = dist(rng);

		while (!_getNeighbour(V, t))
			t = dist(rng);

		switch (t)
		{
		case 1:
		{
			Vertex* vt = new Vertex(V->x + 1, V->y, 1);
			V->addEdge(vt);
			_createPath(graph, vt);
			break;
		}
		case 2:
		{
			Vertex* vt = new Vertex(V->x - 1, V->y, 2);
			V->addEdge(vt);
			_createPath(graph, vt);
			break;
		}
		case 3:
		{
			Vertex* vt = new Vertex(V->x, V->y + 1, 3);
			V->addEdge(vt);
			_createPath(graph, vt);
			break;
		}
		case 4:
		{
			Vertex* vt = new Vertex(V->x, V->y - 1, 4);
			V->addEdge(vt);
			_createPath(graph, vt);
			break;
		}
		}
		_createPath(graph,V);
	}
}

bool Maze::_getNeighbour(Vertex* V, int t)
{
	switch (t)
	{
	case 1:
		if ((V->x + 1 >= 0 && V->x + 1 < width) && maze[V->y][V->x + 1])
			return true;
		break;

	case 2:
		if ((V->x - 1 >= 0 && V->x - 1 < width) && maze[V->y][V->x - 1])
			return true;
		break;

	case 3:
		if ((V->y + 1 >= 0 && V->y + 1 < height) && maze[V->y + 1][V->x])
			return true;
		break;

	case 4:
		if ((V->y - 1 >= 0 && V->y - 1 < height) && maze[V->y - 1][V->x])
			return true;
		break;
	}
	return false;
}

void Maze::createMaze()
{
	_createPath(graph,new Vertex(0,0,0));


	for(auto i = graph.Edges.begin(); i!=graph.Edges.end(); i++)
	{
		for (auto j = (*i)->Edges.begin(); j != (*i)->Edges.end(); j++)
		{
			int x = (*j)->x;
			int y = (*j)->y;
			int k = y * width + x;

			switch ((*j)->d)
			{
			case 1:
				cell->removeSide(k, 2);
				x--; k = y * width + x;
				if (k >= 0 && k < cell->nframe)
					cell->removeSide(k, 1);
				break;
			case 2:
				cell->removeSide(k, 1);
				x++; k = y * width + x;
				if (k >= 0 && k < cell->nframe)
					cell->removeSide(k, 2);
				break;
			case 3:
				cell->removeSide(k, 4);
				y--; k = y * width + x;
				if (k >= 0 && k < cell->nframe)
					cell->removeSide(k, 3);
				break;
			case 4:
				cell->removeSide(k, 3);
				y++; k = y * width + x;
				if (k >= 0 && k < cell->nframe)
					cell->removeSide(k, 4);
				break;
			}
		}
	}
	
}

void Maze::findPath()
{
	deque<Vertex*> que;
	Vertex*** pred;

	pred = new Vertex**[height];
	for (int i = 0; i < height; i++)
	{
		pred[i] = new Vertex*[width];
		for (int j = 0; j < width; j++)
		{
			pred[i][j] = nullptr;
		}
	}

	que.push_back(graph.Edges.front());

	while (!que.empty())
	{
		maze[que[0]->y][que[0]->x] = 1;

		if (que[0]->x == width - 1 && que[0]->y == height - 1)
		{
			spath.push_front(pair<int,int>(width - 1, height - 1));
			break;
		}

		for (auto i = que[0]->Edges.begin(); i != que[0]->Edges.end(); i++)
		{
			if (!maze[(*i)->y][(*i)->x])
			{
				que.push_back(*i);
				pred[(*i)->y][(*i)->x] = que[0];
			}
		}
		que.pop_front();
	}

	Vertex* tmp = que[0];
	while (tmp)
	{
		spath.push_front(pair<int,int>(tmp->x, tmp->y));
		tmp = pred[tmp->y][tmp->x];
	}

	int i = 0, k = 0;
	while (i!=spath.size()-1)
	{
		k = spath[i].second*width + spath[i].first;
		cell->setValue(" * ", k);
		i++;
	}
	cell->setValue(" S ", 0);
	cell->setValue(" E ", cell->nframe - 1);
}

void Maze::load()
{
	cell->load();
	Layer::load();
}

void Maze::render(double &dt)
{

	for (int i = 0; i < cell->nframe; i++)
	{
		cell->cell = i;

		cell->render(dt);

		cell->x += cell->width;

		if (cell->x >= (cell->width*width))
		{
			cell->x = 0;
			cell->y += cell->height;
		}
	}
	cell->x = 0;
	cell->y = 0;
	Layer::render(dt);
}