#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "DisplayObject.h"
#include  "Move.h"

class Enemy : public DisplayObject {
public:
	Enemy();
	~Enemy();

	// Draw the object
	void draw();

	// Update the object
	void update();

	void move(Move newMove);
	glm::vec2 getStartPos() { return  m_startPos; }
	glm::vec2 getEndPos() { return  m_endPos; }
	void setStartPos(glm::vec2 sPos);
	void setEndPos(glm::vec2 ePos);

	void setCurrentDirection(Move cDirection);
	Move getCurrentDirection() { return m_currentDirection; }
	// remove anything that needs to be deleted
	void clean();

	bool onShadow;

	bool isGrounded;
	bool isCollidingPlayer;

private:
	glm::vec2 m_startPos;
	glm::vec2 m_endPos;
	float m_maxSpeed;
	Move m_currentDirection;
};
#endif
