#include "Maze.hpp"
#include "Engine/Globals.hpp"
#include <ctime>

int main()
{
	double k = 0.0;
	srand(time(nullptr));
	Scene gm(GAME_WIDTH,GAME_HEIGHT);
	Maze* maze = new Maze(&gm,GAME_WIDTH/5,GAME_HEIGHT/3);
	gm.addLayer(maze);
	gm.load();
	maze->createMaze();
	gm.render(k);
	gm.game.refresh();
	system("pause");
	return 0;
}