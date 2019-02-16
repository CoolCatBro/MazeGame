#pragma once

#include "Engine/Sprite.hpp"
#include "Engine/GameManager.hpp"

class Cell : public Sprite
{
	string value;

public:

	int cell;

	Cell(GameManager* gm,int n);
	void setValue(string value,int n);
	void removeSide(int cell, int side);
	void load();
	void render(double &dt);
};

