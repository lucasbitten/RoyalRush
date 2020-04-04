#include "Door.h"
#include "Game.h"

Door::Door()
{
	TheTextureManager::Instance()->load("../Assets/textures/Door.png", "door",
		TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("door");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::DOOR);
}

Door::~Door()
{
}

void Door::draw()
{
	TheTextureManager::Instance()->draw("door", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Door::update()
{
}

void Door::clean()
{
}
