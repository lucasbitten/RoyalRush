#pragma once
#ifndef __Island__
#define __Island__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Island : public GameObject {
public:
	Island();
	~Island();


	// Inherited via GameObject
	void draw() override;

	void update() override;

	void clean() override;
private:

	void _move();

	void _checkBounds();

	void _reset();
	

};

#endif /* defined (__Island__) */