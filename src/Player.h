#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"
#include  "Move.h"

class Player : public DisplayObject {
public:

	static Player* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Player();
			return s_pInstance;
		}
		return s_pInstance;
	}

	
	Player();
	~Player();

	// Draw the object
	void draw();

	// Update the object
	void update();

	void move(Move newMove);

	void stopJump(glm::vec2 newPos);

	// remove anything that needs to be deleted
	void clean();

	bool onShadow;
	
	bool isGrounded;

	
	float initialJumpVelocity = 100;
	
	float jumpTime = 0;
	float jumpDuration = 1;
	
	bool jumping = false;
	void jump();

	bool isCollidingEnemy;
private:
	static Player* s_pInstance;
	float m_maxSpeed;
};

typedef  Player ThePlayer;

#endif /* defined (__Player__) */