#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__
#include "DisplayObject.h"
#include <sstream>

class Background : public DisplayObject
{
public:
	Background();
	~Background();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif /* define (__BACKGROUND__) */