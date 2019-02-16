#include "Engine/GameManager.hpp"
#include "Maze.hpp"
#include "Player.hpp"
#include <ctime>
#include <conio.h>

int main()
{
	GameManager gm(GAME_WIDTH,GAME_HEIGHT);
	Maze* maze = new Maze(&gm,GAME_WIDTH/5,(GAME_HEIGHT-1)/3);
	Player* pl = new Player(&gm);
	maze->addNode(pl);
	gm.addLayer(maze);
	gm.load();
	maze->createMaze();
	maze->findPath();

	while (1)
	{
		if (_kbhit())
			pl->move(_getch());
		gm.render();
		gm.gameEng.refresh();
	}

	return 0;
}