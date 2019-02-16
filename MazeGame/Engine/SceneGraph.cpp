#include "SceneGraph.hpp"

//Scene-------------------------------------------------------

Scene::Scene(){}

Scene::Scene(int width,int height):gameEng(width,height){}

Scene::~Scene()
{
}

void Scene::addLayer(Layer* layer)
{
	Layers.push_back(layer);
}

void Scene::removeLayer(string id)
{
	for (auto i = Layers.begin(); i != Layers.end(); i++)
		if ((*i)->id == id)
		{
			Layers.erase(i);
			break;
		}
}

Layer* Scene::getLayer(string id)
{
	for (auto i = Layers.begin(); i != Layers.end(); i++)
		if ((*i)->id == id)
			return *i;
	return nullptr;
}

void Scene::load()
{
	for (auto i = Layers.begin(); i != Layers.end(); i++)
		(*i)->load();
}

void Scene::render(double &dt)
{
	for (auto i = Layers.begin(); i != Layers.end(); i++)
		(*i)->render(dt);
}

//Layer-----------------------------------------------------

Layer::Layer(Scene* scene,string id)
{
	this->scene = scene;
	this->id = id;
}

Layer::~Layer()
{
}

void Layer::addNode(Node* node)
{
	Nodes.push_back(node);
}

void Layer::removeNode(string id)
{
	for (auto i = Nodes.begin(); i != Nodes.end(); i++)
	{
		if ((*i)->id == id)
		{
			Nodes.erase(i);
			break;
		}
	}
}

Node* Layer::getNode(string id)
{
	for (auto i = Nodes.begin(); i != Nodes.end(); i++)
		if ((*i)->id == id)
			return *i;
	return nullptr;
}

void Layer::load()
{
	for (auto i = Nodes.begin(); i != Nodes.end(); i++)
		(*i)->load();
}

void Layer::render(double &dt)
{
	for (auto i = Nodes.begin(); i != Nodes.end(); i++)
		(*i)->render(dt);
}

//Node------------------------------------------------------------

Node::Node(Scene* scene,string id)
{
	this->scene = scene;
	this->id = id;
}

Node::~Node()
{
}