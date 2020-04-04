#include  "GroundPlatform.h"
#include "Game.h"

GroundPlatform::GroundPlatform()
{

	TheTextureManager::Instance()->load("../Assets/textures/Ground platform.png",
		"groundPlatform", TheGame::Instance()->getRenderer());

	const glm::vec2 size = TheTextureManager::Instance()->getTextureSize("groundPlatform");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::GROUND);
	setIsColliding(false);


}

GroundPlatform::~GroundPlatform()
= default;

void GroundPlatform::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("groundPlatform", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);

}

void GroundPlatform::update()
{
}

void GroundPlatform::clean()
{
}
