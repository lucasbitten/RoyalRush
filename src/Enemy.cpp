#include "Enemy.h"
#include "Game.h"
#include "Player.h"

Enemy::Enemy() :m_maxSpeed(1.0f)
{
	/*TheTextureManager::Instance()->load("../Assets/textures/Enemy.png", "enemy", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));*/

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	
	std::cout << "Enemy on scene!" << std::endl;

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy");
	setWidth(size.x);
	setHeight(size.y);
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

	switch (m_currentAnimationState)
	{
	case ENEMY_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 0.7f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case ENEMY_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 0.7f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL); 
		break;
	}
	//TheTextureManager::Instance()->draw("enemy", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true, flip);
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

