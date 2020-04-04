#include "Player.h"
#include "Game.h"

Player* Player::s_pInstance;


Player::Player(): m_currentFrame(0), m_currentAnimationState(PLAYER_IDLE_RIGHT), m_maxSpeed(3.0f)
{
	TheSoundManager::Instance()->load("../Assets/audio/jump_02.wav", "jj", SOUND_SFX);

	
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet", TheGame::Instance()->getRenderer());

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");
	
	// set frame width
	setWidth(30);

	// set frame height
	setHeight(30);

	setPosition(glm::vec2(400.0f, 300.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(PLAYER);

	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			getPosition().x, getPosition().y, m_currentFrame, 0.8f,
			TheGame::Instance()->getRenderer(), 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			getPosition().x, getPosition().y, m_currentFrame, 0.8f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 1.0f,
			TheGame::Instance()->getRenderer(), 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			getPosition().x, getPosition().y, m_currentFrame, 1.0f,
			TheGame::Instance()->getRenderer(), 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	}
	
	
	
}

void Player::update()
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

	if (currentPosition.x < 5)
	{
		setPosition(glm::vec2(5, currentPosition.y));
	} else if (currentPosition.x > Config::SCREEN_WIDTH - 5)
	{
		setPosition(glm::vec2(Config::SCREEN_WIDTH - 5, currentPosition.y));

	} else
	{
		setPosition(glm::vec2(currentPosition.x + getVelocity().x, currentPosition.y + getVelocity().y));

	}



	//glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();

	
	if (!isGrounded)
	{
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y + 0.5f));

	}
	
}

void Player::clean()
{
}

void Player::move(Move newMove)
{
	auto currentVelocity = getVelocity();

	switch (newMove)
	{
	case RIGHT:
		setVelocity(glm::vec2(currentVelocity.x + 1, currentVelocity.y));
		flip = SDL_FLIP_NONE;
		
		break;
	case LEFT:
		setVelocity(glm::vec2(currentVelocity.x - 1, currentVelocity.y));
		flip = SDL_FLIP_HORIZONTAL;

		break;
	}


}

void Player::stopJump(glm::vec2 newPos)
{
	setVelocity(getVelocity().x, 0);
	jumping = false;
	jumpTime = 0;
	isGrounded = true;
	//setPosition(newPos);


}



void Player::jump()
{
	TheSoundManager::Instance()->playSound("jj", 0);

	isGrounded = false;
	setVelocity(glm::vec2(getVelocity().x, -11));

}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";

	for (int i = 1; i < 9; ++i)
	{
		idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("player_idle-" + std::to_string(i)));

	}


	m_pAnimations["idle"] = idleAnimation;

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	
	for (int i = 1; i < 9; ++i)
	{
		runAnimation.frames.push_back(m_pSpriteSheet->getFrame("player_run-" + std::to_string(i)));
	}


	m_pAnimations["run"] = runAnimation;
}
