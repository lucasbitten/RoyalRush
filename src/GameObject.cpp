#include "GameObject.h"


GameObject::GameObject():
	m_position(glm::vec2(0, 0)), m_rotation(glm::vec2(0, 0)), m_scale(glm::vec2(0, 0)), m_velocity(glm::vec2(0, 0)),m_acceleration(glm::vec2(0, 0)),
	m_width(0), m_height(0), m_currentRow(0), m_currentFrame(0), m_numFrames(0), m_isColliding(false), m_type(GameObjectType::NONE), m_state(SteeringState::NO_STATE)
{
}

GameObject::~GameObject()
{
}


glm::vec2 GameObject::getPosition()
{
	return m_position;
}

glm::vec2 GameObject::getRotation()
{
	return m_rotation;
}

glm::vec2 GameObject::getScale()
{
	return m_scale;
}

glm::vec2 GameObject::getVelocity()
{
	return m_velocity;
}

glm::vec2 GameObject::getAcceleration()
{
	return m_acceleration;
}

int GameObject::getWidth()
{
	return m_width;
}

int GameObject::getHeight()
{
	return m_height;
}

bool GameObject::getIsColliding()
{
	return m_isColliding;
}

GameObjectType GameObject::getType()
{
	return m_type;
}

SteeringState GameObject::getState()
{
	return m_state;
}


void GameObject::setPosition(glm::vec2 newPosition)
{


	m_position = newPosition;
}

void GameObject::setWidth(int newWidth)
{
	m_width = newWidth;
}

void GameObject::setHeight(int newHeight)
{
	m_height = newHeight;
}

void GameObject::setVelocity(glm::vec2 newVelocity)
{
	m_velocity = newVelocity;
}

void GameObject::setIsColliding(bool collision)
{
	m_isColliding = collision;
}

void GameObject::setType(GameObjectType newType)
{
	m_type = newType;
}

void GameObject::setState(SteeringState newState)
{
	m_state = newState;
}

void GameObject::setAcceleration(glm::vec2 newAcceleration)
{
	m_acceleration = newAcceleration;
}
