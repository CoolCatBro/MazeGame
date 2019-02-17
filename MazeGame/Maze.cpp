#include "Maze.hpp"

Maze::Maze(GameManager *gm,int width, int height)
	 :Layer(gm,"maze"),width(width),height(height),dist(1,4)
{
	maze = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maze[i] = new int[width];
		for (int j = 0; j < width; j++)
			maze[i][j] = 1;
	}

	cell = new Cell(gm, width*height);

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

void Maze::createMaze(bool load)
{
	if(!load)
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

	findPath();
	
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
		if (que[0]->x == width - 1 && que[0]->y == height - 1)
		{
			spath.push_front(pair<int,int>(width - 1, height - 1));
			break;
		}

		for (auto i = que[0]->Edges.begin(); i != que[0]->Edges.end(); i++)
		{
			que.push_back(*i);
			pred[(*i)->y][(*i)->x] = que[0];
		}
		que.pop_front();
	}

	Vertex* tmp = que[0];
	while (tmp)
	{
		spath.push_front(pair<int,int>(tmp->x, tmp->y));
		tmp = pred[tmp->y][tmp->x];
	}

	cell->setValue(" E ", cell->nframe - 1);
}

void Maze::displayPath()
{
	int i = 0, k = 0;
	while (i != spath.size() - 1)
	{
		k = spath[i].second*width + spath[i].first;
		cell->setValue(" * ", k);
		i++;
	}
}

void Maze::saveMaze()
{
	ofstream file;
	file.open("save\\map.txt", std::ios::out);

	deque<Vertex*> que;

	que.push_front(graph.Edges.front());

	while (!que.empty())
	{
		file << que.front()->x << " " << que.front()->y << " " << que.front()->d << " ";
		for (auto i = que.front()->Edges.begin(); i != que.front()->Edges.end(); i++)
		{
			file << (*i)->x<< " " << (*i)->y << " " << (*i)->d << " ";
			que.push_back(*i);
		}
		que.pop_front();
		file << std::endl;
	}

	file.close();
}

void Maze::loadMaze()
{
	reset();

	ifstream file;
	file.open("save\\map.txt",std::ios::in);
	assert(file);

	string temp;
	deque<Vertex*> que;

	que.push_front(new Vertex(0, 0, 0));

	while (getline(file, temp))
	{
		stringstream ss(temp);

		int x=0, y=0, d=0;
		ss >> x; ss >> y; ss >> d;

		graph.addEdge(que.front());

		while (ss>>x && ss>>y && ss>>d)
		{
			Vertex* V = new Vertex(x, y, d);
			que.front()->addEdge(V);
			que.push_back(V);
		}
		que.pop_front();
	}
	file.close();

	createMaze(true);
}

void Maze::reset()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cell->setValue("   ",i*width + j);
			maze[i][j] = 1;
		}
	}
	cell->load();
	graph.clear();
	spath.clear();
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