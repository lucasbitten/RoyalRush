#include "Enemy.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy() :speed(1.0f)
{
	/*TheTextureManager::Instance()->load("../Assets/textures/Enemy.png", "enemy", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));*/

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	
	std::cout << "Enemy on scene!" << std::endl;

	setWidth(35);
	setHeight(35);
	setIsColliding(false);
	setType(GameObjectType::ENEMY);

	m_buildAnimations();
}

Enemy::~Enemy()
{
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

void Enemy::setAnimationState(EnemyAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Enemy::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void Enemy::m_buildAnimations()
{
	Animation runAnimation = Animation();
	runAnimation.name = "run";
	for (int i = 1; i < 9; i++)
	{
		runAnimation.frames.push_back(m_pSpriteSheet->getFrame("enemy-run-" + std::to_string(i)));
	}

	m_pAnimations["run"] = runAnimation;
}

void Enemy::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	if (facingRight)
	{
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 0.4f,
			TheGame::Instance()->getRenderer(), 0, 255, true);

	} else {
		
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 0.4f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL); 
	}
	//TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true, flip);
}

void Enemy::update()
{

	move();

}

bool Enemy::detectPlayer(Player* player)
{

	
	if (!player->onShadow)
	{

		if (player->getPosition().y < getPosition().y + 20 && player->getPosition().y > getPosition().y - 20)
		{

			if (facingRight)
			{
				if (player->getPosition().x > getPosition().x && player->getPosition().x - getPosition().x < detectDistance)
				{
					TheSoundManager::Instance()->playSound("detected", 0);

					return true;
				}
			}
			else
			{
				if (player->getPosition().x < getPosition().x && getPosition().x - player->getPosition().x < detectDistance)
				{
					TheSoundManager::Instance()->playSound("detected", 0);

					return true;

				}
			}
		}

	}

	return false;
}

void Enemy::move()
{
	auto currentVelocity = getVelocity();

	if ( facingRight)
	{
		setVelocity(glm::vec2(speed, currentVelocity.y));
		if(getPosition().x >= maxPos)
		{
			facingRight = false;
			setVelocity(glm::vec2(0, currentVelocity.y));
		}

	} else
	{
		setVelocity(glm::vec2(-speed, currentVelocity.y));
		if (getPosition().x <= minPos)
		{
			facingRight = true;
			setVelocity(glm::vec2(0, currentVelocity.y));

		}
	}

	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));

	
}

void Enemy::clean()
{
}

