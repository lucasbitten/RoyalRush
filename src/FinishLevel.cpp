#include  "FinishLevel.h"
#include "Game.h"

FinishLevel::FinishLevel()
{
	glm::vec2 size;

	if (TheGame::Instance()->m_currentSceneState != LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->load("../Assets/textures/FinishLevel.png",
			"finishLevel", TheGame::Instance()->getRenderer());
		size = TheTextureManager::Instance()->getTextureSize("finishLevel");
		setWidth(size.x);
		setHeight(size.y);
	} else
	{
		setWidth(30);
		setHeight(30);
	}



	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::FINISH_LEVEL);
	setIsColliding(false);


}

FinishLevel::~FinishLevel()
{
}

void FinishLevel::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;
	if (TheGame::Instance()->m_currentSceneState != LEVEL3_SCENE)
	{
		TheTextureManager::Instance()->draw("finishLevel", xComponent, yComponent,
			TheGame::Instance()->getRenderer(), 0, 255, true);
	}


}

void FinishLevel::update()
{
}

void FinishLevel::clean()
{
}
