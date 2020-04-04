#include "TutorialInfo.h"
#include "Game.h"

TutorialInfo::TutorialInfo(std::string imagePath, std::string imageName, GameObjectType type, glm::vec2 position,
	bool isCentered) : m_name(imageName), m_isCentered(isCentered), m_alpha(200)
{
	TheTextureManager::Instance()->load(imagePath,
		m_name, TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_name);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
	setType(type);
}

TutorialInfo::~TutorialInfo()
{
}

void TutorialInfo::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw(m_name, xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, m_alpha, true);
}

void TutorialInfo::update()
{
}

void TutorialInfo::clean()
{
}
