#pragma once

#include "Engine/SceneGraph.hpp"
#include "Engine/Graph.hpp"
#include "Cell.hpp"

#include <deque>
#include <utility>
#include <random>

using std::deque;
using std::pair;

class Maze : public Layer
{
	int** maze;
	
	Graph graph;
	deque<pair<int,int> > spath;

	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> dist;

	void _createPath(Graph& graph,Vertex*);
	bool _getNeighbour(Vertex*, int t);

public:
	int width, height;
	Cell *cell;

	Maze(Scene* scene,int width,int height);
	void createMaze();
	void findPath();
	void render(double &dt);
};

