#pragma once
#ifndef  __KEY__
#define __KEY__

#include "DisplayObject.h"

class Key : public DisplayObject
{
public:

	Key();
	~Key();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerAtGround;

};



#endif
