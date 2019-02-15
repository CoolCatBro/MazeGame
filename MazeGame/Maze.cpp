#include "Maze.hpp"
#include <iostream>
using namespace std;

Maze::Maze(Scene* scene,int width, int height)
	 :Layer(scene,"maze"),width(width),height(height)
{
	maze = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maze[i] = new int[width];
		for (int j = 0; j < width; j++)
			maze[i][j] = 1;
	}

	cell = new Cell(scene, width*height);
	Layer::addNode(cell);
}

void Maze::_createPath(deque<vector<int> >& path,int x, int y,int d=0)
{
	if (maze[y][x])
	{
		path.push_back(vector<int>{d,x,y});
		maze[y][x] = 0;
	}

	if (_getNeighbour(x, y, 1) || _getNeighbour(x, y, 2) || _getNeighbour(x, y, 3) || _getNeighbour(x, y, 4))
	{
		int t = rand() % 4 + 1;

		while (!_getNeighbour(x, y, t))
			t = rand() % 4 + 1;

		switch (t)
		{
		case 1:
			_createPath(path, x + 1, y, 1);
			break;
		case 2:
			_createPath(path, x - 1, y, 2);
			break;
		case 3:
			_createPath(path, x, y + 1, 3);
			break;
		case 4:
			_createPath(path, x, y - 1, 4);
			break;
		}
		_createPath(path,x, y);
	}
}

bool Maze::_getNeighbour(int x, int y, int t)
{
	switch (t)
	{
	case 1:
		if ((x + 1 >= 0 && x + 1 < width) && maze[y][x + 1])
			return true;
		break;

	case 2:
		if ((x - 1 >= 0 && x - 1 < width) && maze[y][x - 1])
			return true;
		break;

	case 3:
		if ((y + 1 >= 0 && y + 1 < height) && maze[y + 1][x])
			return true;
		break;

	case 4:
		if ((y - 1 >= 0 && y - 1 < height) && maze[y - 1][x])
			return true;
		break;
	}
	return false;
}

void Maze::createMaze()
{
	deque<vector<int> > path;
	_createPath(path,0, 0);


	while(!path.empty())
	{
		int x = path.front()[1];
		int y = path.front()[2];
		int i = y * width + x;

		switch (path.front()[0])
		{
		case 1:
			cell->removeSide(i, 2);
			x--; i = y * width + x;
			if(i>=0 && i<cell->nframe)
			cell->removeSide(i, 1);
			break;
		case 2:
			cell->removeSide(i, 1);
			x++; i = y * width + x;
			if (i >= 0 && i < cell->nframe)
			cell->removeSide(i, 2);
			break;
		case 3:
			cell->removeSide(i, 4);
			y--; i = y * width + x;
			if (i >= 0 && i < cell->nframe)
			cell->removeSide(i, 3);
			break;
		case 4:
			cell->removeSide(i, 3);
			y++; i = y * width + x;
			if (i >= 0 && i < cell->nframe)
			cell->removeSide(i, 4);
			break;
		}
		path.pop_front();
	}
	
}

void Maze::render(double &dt)
{

	for (int i = 0; i < cell->nframe; i++)
	{
		cell->cell = i;
		cell->render(dt);
		scene->game.refresh();
		cell->x += cell->width;

		if (cell->x >= (cell->width*width))
		{
			cell->x = 0;
			cell->y += cell->height;
		}
	}
}