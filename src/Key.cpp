#include "Key.h"
#include "Game.h"

Key::Key()
{
	TheTextureManager::Instance()->load("../Assets/textures/Key.png",
		"key", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("key");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::KEY);
	setIsColliding(false);
}

Key::~Key()
{
}

void Key::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("key", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Key::update()
{
}

void Key::clean()
{
}
