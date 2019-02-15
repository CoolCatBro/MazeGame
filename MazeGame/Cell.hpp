#pragma once

#include "Engine/Sprite.hpp"

class Cell : public Sprite
{
	string value;

public:

	int cell;

	Cell(Scene* scene,int n);
	void setValue(string value,int n);
	void removeSide(int cell, int side);
	void load();
	void render(double &dt);
};

