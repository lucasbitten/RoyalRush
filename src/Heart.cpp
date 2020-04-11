#include "Heart.h"
#include "TextureManager.h"
#include "Game.h"

Heart::Heart()
{
	TheTextureManager::Instance()->load("../Assets/textures/Heart.png",
		"heart", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("heart");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setType(GameObjectType::HEART);

}

Heart::~Heart()
= default;

void Heart::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("heart", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Heart::update()
{

}

void Heart::clean()
{
}

