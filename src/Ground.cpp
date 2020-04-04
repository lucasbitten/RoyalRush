#include  "Ground.h"
#include "Game.h"

Ground::Ground()
{
	glm::vec2 size;
	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->load("../Assets/textures/GroundCastle.png",
			"groundCastle", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("groundCastle");

	} else
	{
		TheTextureManager::Instance()->load("../Assets/textures/Ground.png",
			"ground", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("ground");

	}



	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::GROUND);
	setIsColliding(false);

	
}

Ground::~Ground()
{
}

void Ground::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->draw("groundCastle", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, true);
	}
	else
	{
		TheTextureManager::Instance()->draw("ground", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, true);
	}


	
}

void Ground::update()
{
}

void Ground::clean()
{
}
