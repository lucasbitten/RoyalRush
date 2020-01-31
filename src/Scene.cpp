#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
}


void Scene::addChild(DisplayObject * child)
{
	m_displayList.push_back(child);
}

void Scene::removeAllChildren()
{
	for(auto child : m_displayList)
	{
		child = NULL;
	}
	m_displayList.clear();
	m_displayList.resize(0);
	m_displayList.shrink_to_fit();
}


int Scene::numberOfChildren()
{
	return m_displayList.size();
}
