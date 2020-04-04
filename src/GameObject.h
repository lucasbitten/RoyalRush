#pragma once
#ifndef __GameObject__
#define __GameObject__

#include <glm/vec2.hpp>
#include <string>

// enums
#include "GameObjectType.h"

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	glm::vec2 getPosition() const;
	glm::vec2 getRotation() const;
	glm::vec2 getScale() const;
	glm::vec2 getVelocity() const;
	glm::vec2 getAcceleration() const;
	int getWidth() const;
	int getHeight() const;
	bool getIsColliding() const;
	GameObjectType getType() const;

	// setters for common variables
	void setPosition(glm::vec2 new_position);
	void setPosition(float x, float y);
	void setWidth(int new_width);
	void setHeight(int new_height);
	void setVelocity(glm::vec2 new_velocity);
	void setVelocity(float x, float y);
	void setIsColliding(bool collision);
	void setType(GameObjectType new_type);
	void setAcceleration(glm::vec2 new_acceleration);

private:
	// transform variables
	glm::vec2 m_position;
	glm::vec2 m_rotation;
	glm::vec2 m_scale;

	// movement variables
	glm::vec2 m_velocity;
	glm::vec2 m_acceleration;

	// size variables
	int m_width;
	int m_height;

	// animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;

	// collision variables
	bool m_isColliding;
	GameObjectType m_type;
};

#endif