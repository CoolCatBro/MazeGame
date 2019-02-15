#pragma once

#include "Engine/SceneGraph.hpp"
#include "Cell.hpp"

#include <deque>
using std::deque;

class Maze : public Layer
{
	int** maze,width,height;
	Cell *cell;

	void _createPath(deque<vector<int> >& path,int x,int y,int d);
	bool _getNeighbour(int x, int y, int t);

public:
	Maze(Scene* scene,int width,int height);
	void createMaze();
	void render(double &dt);
};

