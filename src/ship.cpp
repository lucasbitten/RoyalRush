#include "ship.h"
#include "Game.h"
#include "Util.h"
#include "GLM/gtx/rotate_vector.hpp"
#include "PlayScene.h"
#include "GLM/gtx/string_cast.hpp"


Ship::Ship() :
	m_maxSpeed(5.0f), m_currentDirection(0.0f), m_turnSpeed(2.0f), m_steerForce(0.1f), m_currentTile(NULL)
{
	TheTextureManager::Instance()->load("../Assets/textures/ship3.png",
		"ship", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(GameObjectType::SHIP);
	setState(SteeringState::IDLE);
}


Ship::~Ship()
{
}

void Ship::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), m_currentDirection, 255, true);
}

void Ship::m_checkState()
{
	switch (getState())
	{
	case SteeringState::IDLE:
		move();
		break;
	case SteeringState::SEEK:
		m_seek();
		//move();
		break;
	case SteeringState::ARRIVE:
		break;
	case SteeringState::AVOID:
		break;
	case SteeringState::FLEE:
		break;
	}
}

void Ship::update()
{
	move();
}

void Ship::clean()
{
	delete m_currentTile;
	m_currentTile = NULL;
}

void Ship::turnRight()
{
	m_currentDirection += m_turnSpeed;
	if (m_currentDirection >= 360) 
	{
		m_currentDirection = 0;
	}

}

void Ship::turnLeft()
{
	m_currentDirection -= m_turnSpeed;
	if (m_currentDirection < 0)
	{
		m_currentDirection = 359.0;
	}
}

void Ship::move()
{
	if (Util::distance(getPosition(), m_target) > 1.0f) {
		glm::vec2 desired = Util::normalize(m_target - getPosition()) * m_maxSpeed;
		setVelocity(desired);


		glm::vec2 newPosition = getPosition() + getVelocity();
		setPosition(newPosition);
	}
	

}

Tile * Ship::getTile()
{
	return m_currentTile;
}

void Ship::setTile(Tile* newTile)
{
	m_currentTile = newTile;
}

glm::vec2 Ship::getTarget()
{
	return m_target;
}

void Ship::setTarget(glm::vec2 position)
{
	m_target = position;
}


void Ship::m_checkBounds()
{

	if (getPosition().x > Config::SCREEN_WIDTH)
	{
		setPosition(glm::vec2(0.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(800.0f, getPosition().y));
	}

	if (getPosition().y > Config::SCREEN_HEIGHT)
	{
		setPosition(glm::vec2(getPosition().x, 0.0f));
	}

	if (getPosition().y < 0)
	{
		setPosition(glm::vec2(getPosition().x, 600.0f));
	}

}

void Ship::m_reset()
{
	setIsColliding(false);
	int halfWidth = getWidth() * 0.5;
	int xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	int yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}

void Ship::m_seek()
{
	glm::vec2 desired = Util::normalize(m_target - getPosition()) * m_maxSpeed;
	glm::vec2 steer = (desired - getVelocity());

	steer = Util::limitMagnitude(steer, m_steerForce);
	setAcceleration(steer);
}
