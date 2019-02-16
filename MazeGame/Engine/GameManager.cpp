#include "GameManager.hpp"

GameManager::GameManager(int width, int height)
	        :Scene(width,height),score(0),lives(3)
{
	t = 0.0;
}

void GameManager::render()
{
	if (lives > 0)
	{
		Scene::render(t);
		gameEng.mvprintW(1, GAME_HEIGHT - 1, "Score:" + std::to_string(score));
		gameEng.mvprintW(GAME_WIDTH - 8, GAME_HEIGHT - 1, "Lives:" + std::to_string(lives));
	}
	else
	{
		gameEng.clear();
		gameEng.mvprintW(GAME_WIDTH/2 - 5, GAME_HEIGHT/2, "GAME OVER");
		gameEng.refresh();
		Sleep(2500);
	}
}