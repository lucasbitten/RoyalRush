#include "Island.h"
#include "Game.h"

Island::Island()
{
	TheTextureManager::Instance()->load("../Assets/textures/island.png",
		"island", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("island");
	setWidth(size.x);
	setHeight(size.y);
	setVelocity(glm::vec2(0, 5));
	_reset();
	setIsColliding(false);
	setType(GameObjectType::ISLAND);

	TheSoundManager::Instance()->load("../Assets/audio/yay.ogg", 
		"yay", sound_type::SOUND_SFX);
}

Island::~Island()
{
}

void Island::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("island", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Island::update()
{
	_move();
	_checkBounds();
}

void Island::clean()
{
}

void Island::_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity();
	setPosition(newPosition);
}

void Island::_checkBounds()
{
	if (getPosition().y > 480 + getHeight()) {
		_reset();
	}
}

void Island::_reset()
{
	setIsColliding(false);
	int halfWidth = getWidth() * 0.5;
	int xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	int yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}
