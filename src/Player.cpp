#include "Player.h"
#include "Game.h"
#include "PhysicsManager.h"

Player* Player::s_pInstance;

Player::Player()
{
	TheTextureManager::Instance()->load("../Assets/textures/Player.png", "player", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));

	std::cout << "Player on scene!" << std::endl;
	
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);

	TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
		"engine", sound_type::SOUND_MUSIC);

	TheSoundManager::Instance()->playMusic("engine", -1);

	jumpHeight = 1 * ThePhysicsManager::Instance()->pixelsPerMeter;
	initialJumpVelocity = 4;
	timeToApex = 0.5;
	
}

Player::~Player()
{
}

void Player::draw()
{
	TheTextureManager::Instance()->draw("player", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Player::update()
{
	//glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();

	//setPosition(glm::vec2(mouseVector.x, mouseVector.y));
	_move();
	//std::cout << "Player velocity: x = " << getVelocity().x << " Y = " << getVelocity().y << std::endl;

	if(jumping)
	{
		jump();
	}
}

void Player::_move()
{
	glm::vec2 newPosition = getPosition() + getVelocity();
	setPosition(newPosition);
}

void Player::stopJump(glm::vec2 newPos)
{
	jumping = false;
	jumpTime = 0;
	setPosition(newPos);
}

void Player::clean()
{
}

void Player::jump()
{
	
	float posY = getPosition().y;
	posY -= ( 80*jumpTime - ThePhysicsManager::Instance()->gravity * glm::pow(jumpTime,2)/2);
	setPosition(glm::vec2(getPosition().x, posY));
	jumpTime += 0.016;

	if(jumpTime >= jumpDuration)
	{
		posY = getPosition().y;
		posY += (ThePhysicsManager::Instance()->gravity * glm::pow(jumpTime, 2) / 2);

		setPosition(glm::vec2(getPosition().x, posY));
	
	}
}
