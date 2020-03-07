#include "Player.h"
#include "Game.h"
#include "PhysicsManager.h"

Player* Player::s_pInstance;

Player::Player(): m_maxSpeed(5.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/Player.png", "player", TheGame::Instance()->getRenderer());
	setPosition(glm::vec2(200, 200));

	std::cout << "Player on scene!" << std::endl;
	
	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setIsColliding(false);
	setType(GameObjectType::PLAYER);

	//TheSoundManager::Instance()->load("../Assets/audio/engine.ogg",
	//	"engine", sound_type::SOUND_MUSIC);

	//TheSoundManager::Instance()->playMusic("engine", -1);


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
	auto currentPosition = getPosition();
	if(getVelocity().x > 0.0f && getVelocity().x - currentPosition.x < m_maxSpeed )
	{
		setVelocity(glm::vec2(m_maxSpeed, getVelocity().y));
	}

	if (getVelocity().x < 0.0f && currentPosition.x - getVelocity().x > m_maxSpeed)
	{
		setVelocity(glm::vec2(-m_maxSpeed, getVelocity().y));
	}


	if(getPosition().x >= 800)
	{
		setPosition(glm::vec2(790, currentPosition.y + getVelocity().y));
	}
	else if(getPosition().x <= 10)
	{
		setPosition(glm::vec2(11, currentPosition.y + getVelocity().y));
	}
	else {
		setPosition(glm::vec2(currentPosition.x + getVelocity().x, currentPosition.y + getVelocity().y));
	}
	
	//glm::vec2 mouseVector = TheGame::Instance()->getMousePosition();


	if(!isGrounded)
	{
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y + 0.5f));

	}

}

void Player::move(Move newMove)
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
	setVelocity(glm::vec2(getVelocity().x, -10));

}
