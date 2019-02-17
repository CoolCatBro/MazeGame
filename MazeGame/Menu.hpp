#pragma once

#include "Engine/Globals.hpp"
#include "Engine/SceneGraph.hpp"
#include "Maze.hpp"
#include "Player.hpp"

class Menu : public Layer
{
	Maze* maze;
	Player* pl;
	GameManager *gm;

public:
	Menu(GameManager* gm);

	bool getMenu(char key);

	void loadGame();
	void saveGame();
	void newGame();
	void resumeGame();

	void load();
	void render(double& dt);
};

