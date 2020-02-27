#include "Enemy.h"
#include "Game.h"

Enemy::Enemy() :m_maxSpeed(2.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/Enemy.png", "enemy", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));

	std::cout << "Enemy on scene!" << std::endl;

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Enemy::update()
{
	auto currentPosition = getPosition();
	if (getVelocity().x > 0.0f && getVelocity().x - currentPosition.x < m_maxSpeed)
	{
		setVelocity(glm::vec2(m_maxSpeed, getVelocity().y));
	}

	if (getVelocity().x < 0.0f && currentPosition.x - getVelocity().x > m_maxSpeed)
	{
		setVelocity(glm::vec2(-m_maxSpeed, getVelocity().y));
	}



	setPosition(glm::vec2(currentPosition.x + getVelocity().x, currentPosition.y + getVelocity().y));
	if (!isGrounded)
	{
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y + 0.5f));

	}
}

void Enemy::move(Move newMove)
{
	auto currentVelocity = getVelocity();

	switch (newMove)
	{
	case RIGHT:
		setVelocity(glm::vec2(currentVelocity.x + 5, currentVelocity.y));
		break;
	case LEFT:
		setVelocity(glm::vec2(currentVelocity.x - 5, currentVelocity.y));
		break;
	}
}

void Enemy::setStartPos(glm::vec2 sPos)
{
	m_startPos = sPos;
}

void Enemy::setEndPos(glm::vec2 ePos)
{
	m_endPos = ePos;
}

void Enemy::setCurrentDirection(Move cDirection)
{
	m_currentDirection = cDirection;
}


void Enemy::clean()
{
}
