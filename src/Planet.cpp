#include "Planet.h"
#include "Game.h"

Planet::Planet():
	m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/planet.png",
		"planet", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("planet");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0.0f, 0.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setType(GameObjectType::PLANET);
}

Planet::~Planet()
{
}

void Planet::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("planet", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, true);
}

void Planet::update()
{
}

void Planet::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

Tile * Planet::getTile()
{
	return m_currentTile;
}

void Planet::setTile(Tile * newTile)
{
	m_currentTile = newTile;
}