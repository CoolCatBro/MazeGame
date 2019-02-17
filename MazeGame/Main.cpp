#include "Engine/GameManager.hpp"
#include "Menu.hpp"
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

	Menu* menu = new Menu(&gm);
	gm.addLayer(menu);

	gm.load();

	menu->getMenu('1');
	gm.addLayer(menu);

	char ch;
	bool menuactive = true;
	while (1)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 27 && !menuactive)
			{
				gm.addLayer(menu);
				menuactive = true;
			}
			if (menuactive)
			{
				if (menu->getMenu(ch))
					menuactive = false;
			}
			else
			{
				pl->move(ch);
			}
		}
		gm.render(menuactive);
		gm.gameEng.refresh();
		if (gm.lives <= 0)
		{
			menu->getMenu('1');
			gm.addLayer(menu);
			menuactive = true;
		}
	}

	return 0;
}