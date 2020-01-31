#pragma once
#ifndef __CollisionManager__
#define __CollisionManager__

// core libraries
#include <iostream>

#include "GameObject.h"
#include <GLM/gtx/norm.hpp>
#include "SoundManager.h"
#include "Player.h"
class CollisionManager
{
public:
	static int squaredDistance(glm::vec2 P1, glm::vec2 P2);
	static bool squaredRadiusCheckPlayer(Player* player, GameObject* object2);
	static bool squaredRadiusCheck(GameObject* object1, GameObject* object2);

	static bool AABBCheck(GameObject* object1, GameObject* object2);

	static bool lineLineCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End);
	static bool lineRectCheck(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 recStart, float recWidth, float recHeight);
	static int minSquaredDistanceLineLine(glm::vec2 line1Start, glm::vec2 line1End, glm::vec2 line2Start, glm::vec2 line2End);


	static int circleAABBsquaredDistance(glm::vec2 circleCentre, int circleRadius, glm::vec2 boxStart, int boxWidth, int boxHeight);
	static bool circleAABBCheck(GameObject* object1, GameObject* object2);

private:
	CollisionManager();
	~CollisionManager();
};

typedef CollisionManager Collision;

#endif /* defined (__CollisionManager__) */