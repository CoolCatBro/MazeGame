#pragma once

#include <cstdlib>
#include <iostream>
#include <stack>

using std::cout;

class Maze
{
	int** maze,width,height;

	void _create(int x,int y);
	bool _getNeighbour(int x, int y, int t);
public:
	Maze(int width,int height);
	void createMaze();
	void display();
};

