#include "Target.h"
#include "Game.h"

Target::Target()
{
	TheTextureManager::Instance()->load("../Assets/textures/Circle.png",
		"circle", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("circle");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(100.0f, 100.0f));
	setVelocity(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::TARGET);
}

Target::~Target()
{
}

void Target::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	TheTextureManager::Instance()->draw("circle", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity() * 5.0f;
	setPosition(newPosition);
}

void Target::m_checkBounds()
{
}

void Target::m_reset()
{
}
