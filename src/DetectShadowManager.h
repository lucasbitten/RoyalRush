#pragma once
#pragma once
#ifndef __DetectShadowManager__
#define __DetectShadowManager__

// core libraries
#include <iostream>

#include "GameObject.h"
#include <GLM/gtx/norm.hpp>
#include "Shadow.h"
#include "Player.h"
#include "SoundManager.h"

class DetectShadowManager
{
public:
	static int squaredDistance(glm::vec2 P1, glm::vec2 P2);
	static void playerOnShadow(Shadow* shadow, Player* player);

private:

	DetectShadowManager();
	~DetectShadowManager();


};

typedef DetectShadowManager ShadowCollision;

#endif /* defined (__DetectShadowManager__) */
