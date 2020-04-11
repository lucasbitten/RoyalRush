#pragma once
#ifndef __HEART__
#define __HEART__
#include "DisplayObject.h"

class Heart : public DisplayObject
{
public:
	Heart();
	~Heart();

	void draw() override;
	void update() override;
	void clean() override;
private:

};

#endif /* define (__HEART__) */