#pragma once

#include "Engine/Globals.hpp"
#include "Engine/GameManager.hpp"
#include "Maze.hpp"

class Player : public Node
{
	Maze* maze;
	GameManager* gm;

	int mv;
public:

	int level;
	int x, y;

	Player(GameManager* gm);
	void move(char dir);
	void savePlayer();
	void loadPlayer();
	void reset();
	void load();
	void render(double& dt);
};

