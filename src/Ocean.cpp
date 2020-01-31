#include "Ocean.h"
#include "Game.h"

Ocean::Ocean()
{
	TheTextureManager::Instance()->load("../Assets/textures/ocean.gif",
		"ocean", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("ocean");
	setWidth(size.x);
	setHeight(size.y);
	setVelocity(glm::vec2(0, 5));
	_reset();
	setIsColliding(false);
	setType(GameObjectType::OCEAN);
}

Ocean::~Ocean()
{
}

void Ocean::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("ocean", xComponent, yComponent,
		TheGame::Instance()->getRenderer());
}

void Ocean::update()
{
	_move();
	_checkBounds();
}

void Ocean::clean()
{
}

void Ocean::_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity();
	setPosition(newPosition);
}

void Ocean::_checkBounds()
{
	if (getPosition().y >= 0) 
	{
		_reset();
	}
}

void Ocean::_reset()
{
	setPosition(glm::vec2(0, -960));
}
