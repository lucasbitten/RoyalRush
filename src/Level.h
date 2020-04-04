#pragma once
#ifndef __LEVEL__
#define __LEVEL__
#include <string>
#include <vector>
#include "Layer.h"

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeigth;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level
{
public:
	Level();
	~Level();

	void update();
	void render();

	std::vector<Tileset>* getTileset()
	{
		return &m_tilesets;
	}

	std::vector<Layer*>* getLayers()
	{
		return &m_layers;
	}
private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
};



#endif /* define (__LEVEL__) */