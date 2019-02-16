#pragma once

#include "Engine/SceneGraph.hpp"
#include "Engine/Graph.hpp"
#include "Engine/GameManager.hpp"
#include "Cell.hpp"

#include <deque>
#include <utility>
#include <random>
#include <sstream>
#include <fstream>

using std::deque;
using std::pair;
using std::stringstream;
using std::ifstream;
using std::ofstream;

class Maze : public Layer
{
	int** maze;
	
	Graph graph;

	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> dist;

	void _createPath(Graph& graph,Vertex*);
	bool _getNeighbour(Vertex*, int t);

public:
	int width, height;
	Cell *cell;
	deque<pair<int, int> > spath;

	Maze(GameManager* gm,int width,int height);

	void createMaze(bool load=false);
	void findPath();
	void displayPath();

	void saveMaze();
	void loadMaze();

	void reset();

	void load();
	void render(double &dt);
};

