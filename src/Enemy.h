#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"
#include "Player.h"
#include "EnemyAnimationState.h"

class Enemy : public DisplayObject {
public:
	Enemy();
	~Enemy();

	// Draw the object
	void draw();

	// Update the object
	void update();

	bool detectPlayer(Player*);
	void move();

	// remove anything that needs to be deleted
	void clean();

	bool onShadow;

	bool isGrounded;

	bool facingRight = true;
	float detectDistance = 80;

	void setPatrolRange(float range);
	void setRange();
	void setSpeed(float speed);

	// SetAnimations for Enemy
	void setAnimationState(EnemyAnimationState new_state);
	void setAnimation(const Animation& animation);
private:

	float patrolRange = 70;
	float speed = 3;
	float maxPos;
	float minPos;

	SpriteSheet* m_pSpriteSheet;
	int m_currentFrame;
	
	void m_buildAnimations();
	EnemyAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};
#endif
