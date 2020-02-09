#pragma once
#ifndef __Shadow__
#define __Shadow__

#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"

class Shadow : public DisplayObject
{
public:

	Shadow();
	~Shadow();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerAtShadow;
private:

};


#endif /* defined (__Shadow__) */