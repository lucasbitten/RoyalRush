#pragma once
#ifndef __TileComparators__
#define __TileComparators__

#include "Tile.h"

class ComparatorByValue
{
public:
	bool operator() (Tile * tileA, Tile * tileB)
	{
		return tileA->getTileValue() < tileB->getTileValue();
	}
};

#endif /* defined (__TileComparators__) */
