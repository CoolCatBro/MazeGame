#pragma once

#include "Engine/Globals.hpp"
#include "Maze.hpp"

class Player : public Node
{
	int x, y;
	Maze* maze;

public:
	Player(Scene* scene);
	void move(char dir);
	void load();
	void render(double& dt);
};

