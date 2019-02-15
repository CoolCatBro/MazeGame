#include "Maze.hpp"

Maze::Maze(int width, int height)
	 :width(width),height(height)
{
	maze = new int*[height];
	for (int i = 0; i < height; i++)
	{
		maze[i] = new int[width];
		for (int j = 0; j < width; j++)
			maze[i][j] = 1;
	}
}

void Maze::_create(int x, int y)
{
	maze[y][x] = 0;

	if (_getNeighbour(x, y, 1) || _getNeighbour(x, y, 2) || _getNeighbour(x, y, 3) || _getNeighbour(x, y, 4))
	{
		int t = rand() % 4 + 1;

		while (!_getNeighbour(x, y, t))
			t = rand() % 4 + 1;

		if (t == 1)
			_create(x + 1, y);
		else if (t == 2)
			_create(x - 1, y);
		else if (t == 3)
			_create(x, y + 1);
		else if (t == 4)
			_create(x, y - 1);

		_create(x, y);
	}
}

bool Maze::_getNeighbour(int x, int y, int t)
{
	if (t == 1)
	{
		if ((x + 1 >= 0 && x + 1 < width) && maze[y][x + 1])
			return true;
	}
	if (t == 2)
	{
		if ((x - 1 >= 0 && x - 1 < width) && maze[y][x - 1])
			return true;
	}
	if (t == 3)
	{
		if ((y + 1 >= 0 && y + 1 < height) && maze[y + 1][x])
			return true;
	}
	if (t == 4)
	{
		if ((y - 1 >= 0 && y - 1 < height) && maze[y - 1][x])
			return true;
	}
	return false;
}

void Maze::createMaze()
{
	_create(0, 0);
}

void Maze::display()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (maze[i][j] == 0)
				cout << '0';
			else
				cout << char(219);
		}
		cout << std::endl;
	}
}