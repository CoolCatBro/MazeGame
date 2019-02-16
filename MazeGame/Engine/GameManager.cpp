#include "GameManager.hpp"

GameManager::GameManager(int width, int height)
	        :Scene(width,height),score(0),lives(3)
{
	t = 0.0;
}


void GameManager::render()
{
	Scene::render(t);
	game.mvprintW(1,GAME_HEIGHT-1, "Score:" + std::to_string(score));
}