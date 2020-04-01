#include "GameObject.h"

GameObject::GameObject():
	m_position(glm::vec2(0, 0)), m_rotation(glm::vec2(0, 0)), m_scale(glm::vec2(0, 0)), m_velocity(glm::vec2(0, 0)),m_acceleration(glm::vec2(0, 0)),
	m_width(0), m_height(0), m_currentRow(0), m_currentFrame(0), m_numFrames(0), m_isColliding(false), m_type(GameObjectType::NONE)
{
}

GameObject::~GameObject()
= default;

glm::vec2 GameObject::getPosition() const
{
	
	return m_position;
}

glm::vec2 GameObject::getRotation() const
{
	return m_rotation;
}

glm::vec2 GameObject::getScale() const
{
	return m_scale;
}

glm::vec2 GameObject::getVelocity() const
{
	return m_velocity;
}

glm::vec2 GameObject::getAcceleration() const
{
	return m_acceleration;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

bool GameObject::getIsColliding() const
{
	return m_isColliding;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}


void GameObject::setPosition(const glm::vec2 new_position)
{
	m_position = new_position;
}

void GameObject::setPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setVelocity(const glm::vec2 new_velocity)
{
	m_velocity = new_velocity;
}

void GameObject::setVelocity(const float x, const float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}

void GameObject::setIsColliding(const bool collision)
{
	m_isColliding = collision;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}


void GameObject::setAcceleration(const glm::vec2 new_acceleration)
{
	m_acceleration = new_acceleration;
}
