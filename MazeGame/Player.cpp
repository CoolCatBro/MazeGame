#include "Player.hpp"



Player::Player(Scene* scene)
	:Node(scene, "player")
{
	x = 0; y = 0;
}

void Player::move(char dir)
{
	maze->cell->setValue(" * ", y*maze->width + x);

	if (dir == UP)
		y--;
	if (dir == LEFT)
		x--;
	if (dir == RIGHT)
		x++;
	if (dir == DOWN)
		y++;

}

void Player::load()
{
	maze = (Maze*)scene->getLayer("maze");
}

void Player::render(double& dt)
{
	maze->cell->setValue(" P ", y*maze->width + x);
}

