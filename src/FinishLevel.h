#pragma once
#ifndef  __FINISH_LEVEL_
#define __FINISH_LEVEL_

#include "DisplayObject.h"

class FinishLevel : public DisplayObject
{
public:

	FinishLevel();
	~FinishLevel();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerAtGround;

};



#endif
