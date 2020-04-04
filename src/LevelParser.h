#pragma once
#ifndef __LEVEL_PARSER__
#define __LEVEL_PARSER__
#include "Layer.h"
#include <vector>
#include "Level.h"
#include <glm/detail/type_vec2.hpp>

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot,
		std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement,
		std::vector<Layer*>* pLayers,
		const std::vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_height;
};


#endif /* define (__LEVEL_PARSER__) */