#include "Cloud.h"
#include "Game.h"

Cloud::Cloud()
{
	TheTextureManager::Instance()->load("../Assets/textures/cloud.png",
		"cloud", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("cloud");
	setWidth(size.x);
	setHeight(size.y);
	_reset();
	setIsColliding(false);
	setType(GameObjectType::CLOUD);

	TheTextureManager::Instance()->setAlpha("cloud", 128);

	TheSoundManager::Instance()->load("../Assets/audio/thunder.ogg",
		"thunder", sound_type::SOUND_SFX);
}

Cloud::~Cloud()
{
}

void Cloud::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("cloud", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Cloud::update()
{
	_move();
	_checkBounds();
}

void Cloud::clean()
{
}

void Cloud::_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity();
	setPosition(newPosition);
}

void Cloud::_checkBounds()
{
	if (getPosition().y > 480 + getHeight()) {
		_reset();
	}
}

void Cloud::_reset()
{
	setIsColliding(false);
	int randomVelocityX = (rand() % 5) - 2;
	int randomVelocityY = (rand() % 6) + 5;
	setVelocity(glm::vec2(randomVelocityX, randomVelocityY));
	int halfWidth = getWidth() * 0.5;
	int xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	int yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}
