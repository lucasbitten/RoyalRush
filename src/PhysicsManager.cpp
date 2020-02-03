#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::s_pInstance = 0;

PhysicsManager::PhysicsManager()
{
	pixelsPerMeter = 17.64;
	gravity = pixelsPerMeter * 30;
}

PhysicsManager::~PhysicsManager()
{
}
