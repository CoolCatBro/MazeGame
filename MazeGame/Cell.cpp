#include "Cell.hpp"


Cell::Cell(GameManager* gm,int n)
	 :Sprite(gm,"cell",5,3,0,0,n),cell(0)
{
}

void Cell::setValue(string value,int n=0)
{
	this->value = value;
	for (int i = 0; i < value.length(); i++)
	{
		frames[n][height / 2][i + 1] = value[i];
	}
}

void Cell::removeSide(int cell, int side)
{
	if (side == 1)
	{
		for (int i = 1; i < height-1; i++)
		{
			frames[cell][i][width - 1] = ' ';
		}
	}
	if (side == 2)
	{
		for (int i = 1; i < height-1; i++)
		{
			frames[cell][i][0] = ' ';
		}
	}
	if (side == 3)
	{
		for (int i = 1; i < width - 1; i++)
		{
			frames[cell][height - 1][i] = ' ';
		}
	}
	if (side == 4)
	{
		for (int i = 1; i < width - 1; i++)
		{
			frames[cell][0][i] = ' ';
		}
	}
}

void Cell::load()
{
	ifstream file;

	file.open(id + "\\" + id + ".txt");
	assert(file);

	for (int i = 0; i < nframe; i++)
	{
		for (int j = 0; j < height; j++)
		{
			getline(file, frames[i][j]);
		}
		file.clear();
		file.seekg(0, std::ios::beg);
	}

	file.close();

	for (int i = 0; i < nframe; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				if (frames[i][j][k] == '1')
					frames[i][j][k] = char(219);
			}
		}
	}
}

void Cell::render(double &dt)
{
	for (int i = 0; i < height; i++)
	{
		scene->gameEng.mvprintW(x, y + i, frames[cell][i]);
	}
}