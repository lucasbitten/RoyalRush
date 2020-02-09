#pragma once
#ifndef  __Ground__
#define __Ground__

#include "DisplayObject.h"

class Ground : public DisplayObject
{
public:

	Ground();
	~Ground();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerAtGround;
	
};



#endif
