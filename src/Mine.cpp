#include "Mine.h"
#include "Game.h"

Mine::Mine() :
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/mine.png",
		"mine", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("mine");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::MINE);
}

Mine::~Mine()
{
}

void Mine::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("mine", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Mine::update()
{
}

void Mine::clean()
{
}

Tile * Mine::getTile()
{
	return m_currentTile;
}

void Mine::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}
