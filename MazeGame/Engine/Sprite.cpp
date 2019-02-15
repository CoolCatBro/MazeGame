#include "SceneGraph.hpp"
#include "Sprite.hpp"

Sprite::Sprite(Scene* scene, string id, int width, int height, int x, int y,int nframe)
	: Node(scene,id),width(width),height(height),x(x),y(y),nframe(nframe)
{
	frames = new string*[nframe];
	for (int i = 0; i < nframe; i++)
	{
		frames[i] = new string[height];
	}
}

Sprite::~Sprite(){}

void Sprite::load()
{
	ifstream file;
	for (int i = 0; i < nframe; i++)
	{
		file.open(id+"\\"+id+std::to_string(i)+".txt");
		assert(file);

		for (int j = 0; j < height; j++)
		{
			getline(file, frames[i][j]);
		}

		file.close();
	}
}