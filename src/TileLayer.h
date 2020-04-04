#pragma once
#ifndef __TILE_LAYER__
#define __TILE_LAYER__
#include "Layer.h"
#include <vector>
#include "Level.h"
#include <glm/detail/type_vec2.hpp>

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const std::vector<Tileset>& tilesets);

	virtual void update();
	virtual void render();

	void setTileIDs(const std::vector<std::vector<int>>& data)
	{
		m_tileIDs = data;
	}

	void setTileSize(int tileSize)
	{
		m_tileSize = tileSize;
	}

	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;
	int numRows;
	int m_tileSize;

	glm::vec2 m_position;
	glm::vec2 m_velocity;

	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;
};


#endif /* define (__TILE_LAYER__) */