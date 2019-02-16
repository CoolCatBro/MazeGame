#pragma once

#include "SceneGraph.hpp"
#include "Globals.hpp"

class GameManager:public Scene
{
	double t;
public:
	int score;
	int lives;

	GameManager(int width,int height);
	void render();
};