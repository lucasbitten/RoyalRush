#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>
#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"
#include  "Move.h"

class Player : public DisplayObject
{
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

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void move(Move newMove);

	void stopJump(glm::vec2 newPos);

	bool onShadow;

	bool isGrounded;

	float initialJumpVelocity = 100;

	float jumpTime = 0;
	float jumpDuration = 1;

	bool jumping = false;
	void jump();

	bool isCollidingEnemy;
	
	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);

private:

	static Player* s_pInstance;
	float m_maxSpeed;
	SDL_RendererFlip flip;
	
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	int m_currentFrame;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};

typedef  Player ThePlayer;


#endif /* defined (__PLAYER__) */