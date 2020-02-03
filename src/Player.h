#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

class Player : public GameObject {
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

	void _move();

	void stopJump(glm::vec2 newPos);

	// remove anything that needs to be deleted
	void clean();

	bool onShadow;
	
	float jumpHeight;
	float initialJumpVelocity;
	float timeToApex;
	
	float jumpTime = 0;
	float jumpDuration = 1;
	
	bool jumping = false;
	void jump();
private:
	static Player* s_pInstance;

};

typedef  Player ThePlayer;

#endif /* defined (__Player__) */