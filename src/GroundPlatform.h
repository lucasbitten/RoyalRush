#pragma once
#ifndef  __Ground__PLATFORM__
#define __Ground__PLATFORM__

#include "DisplayObject.h"

class GroundPlatform : public DisplayObject
{
public:

	GroundPlatform();
	~GroundPlatform();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerAtGround;

};



#endif
