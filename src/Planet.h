#pragma once
#ifndef __Planet__
#define __Planet__

#include "DisplayObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Tile.h"
#include "Scene.h"


class Planet : public DisplayObject
{
public:
	Planet();
	~Planet();

	// Inherited via GameObject
	virtual void draw() override;

	virtual void update() override;

	virtual void clean() override;

	// pathfinding behaviours
	Tile* getTile();
	void setTile(Tile* newTile);

private:
	Tile* m_currentTile;
};


#endif /* defined (__Planet__) */