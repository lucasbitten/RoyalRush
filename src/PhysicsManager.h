#pragma once
#ifndef __PhysicsManager__
#define __PhysicsManager__

class PhysicsManager
{
public:
	static PhysicsManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new PhysicsManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	float pixelsPerMeter;
	float gravity;
private:

	PhysicsManager();
	~PhysicsManager();
	
	static PhysicsManager* s_pInstance;


};

	typedef PhysicsManager ThePhysicsManager;


#endif
