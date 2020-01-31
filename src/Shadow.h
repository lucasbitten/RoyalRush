#pragma once
#ifndef __Shadow__
#define __Shadow__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Shadow : public GameObject
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