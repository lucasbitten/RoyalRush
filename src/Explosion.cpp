#include "Explosion.h"
#include "Game.h"
#include <utility>

Explosion::Explosion() : m_currentFrame(0), m_bIsActive(false)
{

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(52);

	// set frame height
	setHeight(52);

	setPosition(glm::vec2(400.0f, 200.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(EXPLOSION);

	m_buildAnimations();

	
}

Explosion::~Explosion()
= default;

void Explosion::draw()
{

	if(m_currentFrame < m_pAnimations["explosion"].frames.size() - 1)
	{
		TheTextureManager::Instance()->playAnimation(
			"spritesheet", m_pAnimations["explosion"],
			getPosition().x, getPosition().y, m_currentFrame, 0.5f,
			TheGame::Instance()->getRenderer(), 0, 255, true);

	} else
	{
		deactivate();
	}


}

void Explosion::update()
{
}

void Explosion::clean()
{
}

void Explosion::activate()
{
	m_currentFrame = 0;
	m_bIsActive = true;
}

void Explosion::deactivate()
{
	setPosition(1000.0f, 1000.0f);
	m_bIsActive = false;
}

bool Explosion::isActive()
{
	return  m_bIsActive;
}

void Explosion::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;

}

void Explosion::m_buildAnimations()
{
	Animation explosionAnimation = Animation();

	explosionAnimation.name = "explosion";

	for (int i = 0; i < 7; ++i)
	{
		explosionAnimation.frames.push_back(m_pSpriteSheet->getFrame("explosion" + std::to_string((i+1))));

	}


	m_pAnimations["explosion"] = explosionAnimation;
	
}
