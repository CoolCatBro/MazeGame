#include "Menu.hpp"


Menu::Menu(GameManager* gm)
	 :Layer(gm,"menu"),gm(gm)
{
}

bool Menu::getMenu(char key)
{
	switch (key)
	{
	case '1':
		newGame();
		return true;
	case '2':
		loadGame();
		return true;
	case '3':
		saveGame();
		break;
	case '4':
		resumeGame();
		return true;
	}
	return false;
}

void Menu::loadGame()
{
	maze->loadMaze();
	pl->loadPlayer();
	scene->removeLayer("menu");
}

void Menu::saveGame()
{
	maze->saveMaze();
	pl->savePlayer();
}

void Menu::newGame()
{
	maze->reset();
	pl->level = 1;
	gm->score = 0;
	gm->lives = 3;
	pl->reset();
	maze->createMaze();
	scene->removeLayer("menu");
}

void Menu::resumeGame()
{
	scene->removeLayer("menu");
}

void Menu::load()
{
	maze = (Maze*)scene->getLayer("maze");
	pl = (Player*)maze->getNode("player");
	Layer::load();
}

void Menu::render(double& dt)
{
	scene->gameEng.clear();
	scene->gameEng.mvprintW(GAME_WIDTH / 2 - 8, GAME_HEIGHT / 2 - 4, " GAME  MENU");
	scene->gameEng.mvprintW(GAME_WIDTH/2 - 8, GAME_HEIGHT/2-2, "1.) New Game");
	scene->gameEng.mvprintW(GAME_WIDTH/2 - 8, GAME_HEIGHT/2-1, "2.) Load Game");
	scene->gameEng.mvprintW(GAME_WIDTH/2 - 8, GAME_HEIGHT/2-0, "3.) Save Game");
	scene->gameEng.mvprintW(GAME_WIDTH/2 - 8, GAME_HEIGHT/2+1, "4.) Resume Game");
}
