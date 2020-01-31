#include "Shadow.h"
#include  "Game.h"

Shadow::Shadow()
{
	TheTextureManager::Instance()->load("../Assets/textures/Shadow.png", "shadow", TheGame::Instance()->getRenderer());
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("shadow");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::SHADOW);
}

Shadow::~Shadow()
{

}

void Shadow::draw()
{
	TheTextureManager::Instance()->draw("shadow", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Shadow::update()
{

}

void Shadow::clean()
{
}

