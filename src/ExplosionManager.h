#pragma once
#ifndef __EXPLOSION_MANAGER__
#define __EXPLOSION_MANAGER__

#include <list>
#include "Explosion.h"

class ExplosionManager
{
public:
	static ExplosionManager* Instance()
	{
		if(s_pInstance == nullptr)
		{
			s_pInstance = new ExplosionManager();
			return  s_pInstance;
		}

		return s_pInstance;
	}

	void clean();
	void update();
	void draw();
	Explosion* getExplosion();
	
private:
	
	ExplosionManager();
	~ExplosionManager();

	int m_explosionNumber;
	bool m_isActive;
	
	void m_buildExplosionPool();
	
	static  ExplosionManager* s_pInstance;
	
	std::list<Explosion*> m_pExplosionPool;
};

#endif
