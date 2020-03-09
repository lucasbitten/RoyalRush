#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"
#include "Player.h"

class Enemy : public DisplayObject {
public:
	Enemy();
	~Enemy();

	// Draw the object
	void draw();

	// Update the object
	void update();

	void detectPlayer(Player*);

	
	void move();

	// remove anything that needs to be deleted
	void clean();

	bool onShadow;

	bool isGrounded;

	bool facingRight = true;
	float detectDistance = 100;
	
	void setRange();
private:

	SDL_RendererFlip flip;
	float patrolRange = 50;
	float m_maxSpeed;
	float maxPos;
	float minPos;
};
#endif
