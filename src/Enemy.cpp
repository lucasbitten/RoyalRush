#include "Enemy.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy() :m_maxSpeed(1.0f)
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


void Enemy::setPatrolRange(float range)
{
	patrolRange = range;
	setRange();
}

void Enemy::setRange()
{
	maxPos = getPosition().x + patrolRange;
	minPos = getPosition().x - patrolRange;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
	TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true, flip);
}

void Enemy::update()
{

	move();

}

void Enemy::detectPlayer(Player* player)
{
	if (!player->onShadow)
	{

		if (player->getPosition().y < getPosition().y + 20 && player->getPosition().y > getPosition().y - 20)
		{

			if (facingRight)
			{
				if (player->getPosition().x > getPosition().x && player->getPosition().x - getPosition().x < detectDistance)
				{
					TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				}
			}
			else
			{
				if (player->getPosition().x < getPosition().x && getPosition().x - player->getPosition().x < detectDistance)
				{
					TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				}
			}
		}

	}
}

void Enemy::move()
{
	auto currentVelocity = getVelocity();

	if ( facingRight)
	{
		setVelocity(glm::vec2(currentVelocity.x + speed, currentVelocity.y));
		if(getPosition().x >= maxPos)
		{
			facingRight = false;
			setVelocity(glm::vec2(0, currentVelocity.y));
			flip = SDL_FLIP_HORIZONTAL;
		}

	} else
	{
		setVelocity(glm::vec2(currentVelocity.x - speed, currentVelocity.y));
		if (getPosition().x <= minPos)
		{
			facingRight = true;
			setVelocity(glm::vec2(0, currentVelocity.y));
			flip = SDL_FLIP_NONE;

		}
	}

	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));
	if (!isGrounded)
	{
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y + 0.5f));

	}
	
}

void Enemy::clean()
{
}

