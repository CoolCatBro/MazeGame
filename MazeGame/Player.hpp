#pragma once

#include "Engine/Globals.hpp"
#include "Engine/GameManager.hpp"
#include "Maze.hpp"

class Player : public Node
{
	Maze* maze;
	GameManager* gm;

public:

	int x, y;

	Player(GameManager* gm);
	void move(char dir);
	void load();
	void render(double& dt);
};

