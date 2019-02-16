#include "Player.hpp"



Player::Player(GameManager* gm)
	:Node(gm, "player"),gm(gm)
{
	x = 0; y = 0;
}

void Player::move(char dir)
{
	maze->cell->setValue(" * ", y*maze->width + x);

	int p = x, q = y;
	if (dir == UP)
	{
		q--;
	}
	if (dir == LEFT)
	{
		p--;
	}
	if (dir == RIGHT)
	{
		p++;
	}
	if (dir == DOWN)
	{
		q++;
	}
	if (pair<int, int>(p, q) == maze->spath[gm->score+1])
	{
		x = p; y = q;
		gm->score++;
	}
	else
		gm->lives--;
}

void Player::load()
{
	maze = (Maze*)scene->getLayer("maze");
}

void Player::render(double& dt)
{
	maze->cell->setValue(PLAYER, y*maze->width + x);
}

