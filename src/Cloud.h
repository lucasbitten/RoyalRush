#pragma once
#ifndef __CLOUD__
#define __CLOUD__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Cloud : public GameObject {
public:
	// Constructor / Destrutor
	Cloud();
	~Cloud();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
private:
	void _move();
	void _checkBounds();
	void _reset();
	
};

#endif // defined(__CLOUD__)

