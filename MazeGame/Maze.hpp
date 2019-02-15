#pragma once

#include "Engine/SceneGraph.hpp"
#include "Graph.hpp"
#include "Cell.hpp"

#include <deque>
#include <utility>

using std::deque;
using std::pair;

class Maze : public Layer
{
	int** maze,width,height;
	Cell *cell;
	Graph graph;
	deque<pair<int,int> > spath;

	void _createPath(Graph& graph,Vertex*);
	bool _getNeighbour(Vertex*, int t);

public:
	Maze(Scene* scene,int width,int height);
	void createMaze();
	void findPath();
	void render(double &dt);
};

