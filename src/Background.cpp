#include "Background.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameManager.h"

Background::Background()
{
	glm::vec2 size;
	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->load("../Assets/textures/Castle Background.png",
			"castleBackground", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("castleBackground");

	} else
	{
		TheTextureManager::Instance()->load("../Assets/textures/background.png",
			"background", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("background");

	}


	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::BACKGROUND);
}

Background::~Background()
{
}

void Background::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	if (TheGame::Instance()->m_currentSceneState == LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->draw("castleBackground", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, false);
	}
	{
		TheTextureManager::Instance()->draw("background", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, false);
	}
	

}

void Background::update()
{
}

void Background::clean()
{
}
