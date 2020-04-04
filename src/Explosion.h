#pragma once
#ifndef __EXPLOSION__
#define __EXPLOSION__

#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

class Explosion : public DisplayObject
{
public:
	Explosion();
	~Explosion();
	
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void activate();
	void deactivate();
	bool isActive();
	
	
	void setAnimation(const Animation& animation);

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;
	bool m_bIsActive;

	int m_currentFrame;

	std::unordered_map<std::string, Animation> m_pAnimations;
};


#endif 
