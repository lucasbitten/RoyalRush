#include  "GroundPlatform.h"
#include "Game.h"

GroundPlatform::GroundPlatform()
{
	glm::vec2 size;
	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->load("../Assets/textures/GroundCastle platform.png",
			"groundCastlePlatform", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("groundCastlePlatform");
	} else
	{
		TheTextureManager::Instance()->load("../Assets/textures/Ground platform.png",
			"groundPlatform", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("groundPlatform");

	}
	


	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::GROUND_PLATFORM);
	setIsColliding(false);


}

GroundPlatform::~GroundPlatform()
= default;

void GroundPlatform::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->draw("groundCastlePlatform", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, true);
	}else
	{
		TheTextureManager::Instance()->draw("groundPlatform", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, true);
	}
	


}

void GroundPlatform::update()
{
}

void GroundPlatform::clean()
{
}
