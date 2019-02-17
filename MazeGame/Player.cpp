#include "Player.hpp"


Player::Player(GameManager* gm)
	:Node(gm, "player"),gm(gm)
{
	x = 0; y = 0; level = 1; mv = 0;
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
	if (pair<int, int>(p, q) == maze->spath[mv+1])
	{
		x = p; y = q;
		gm->score++;
		mv++;
	}
	else
		gm->lives--;
}

void Player::savePlayer()
{
	ofstream file;

	file.open("save\\player.txt", std::ios::out);
	assert(file);

	file << x << " " << y<<" "
		 << level<<" "
		 << gm->score<<" "
		 << gm->lives;
	file.close();
}

void Player::loadPlayer()
{
	ifstream file;

	file.open("save\\player.txt", std::ios::in);
	assert(file);

	file >> x >> y
		 >> level
		 >> gm->score
		 >> gm->lives;
	file.close();


	mv = 0;
	while (maze->spath[mv] != pair<int, int>(x, y))
	{
		int i = maze->spath[mv].second * maze->width + maze->spath[mv].first;
		maze->cell->setValue(" * ", i);
		mv++;
	}
}

void Player::reset()
{
	x = 0; y = 0; mv = 0;
	maze->reset();
	maze->createMaze();
	maze->findPath();
}

void Player::load()
{
	maze = (Maze*)scene->getLayer("maze");
}

void Player::render(double& dt)
{
	maze->cell->setValue(PLAYER, y*maze->width + x);

	if (x == maze->width - 1 && y == maze->height - 1)
	{
		gm->gameEng.clear();
		gm->gameEng.mvprintW(GAME_WIDTH / 2 - 5, GAME_HEIGHT / 2, "LEVEL:" + std::to_string(++level));
		gm->gameEng.refresh();
		Sleep(2000);
		reset();
		gm->render();
	}
}

