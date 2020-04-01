#include "ExplosionManager.h"

ExplosionManager* ExplosionManager::s_pInstance = nullptr;

void ExplosionManager::clean()
{
}

void ExplosionManager::update()
{
	for (auto explosion : m_pExplosionPool)
	{
		if(explosion->isActive())
		{
			explosion->update();

		}
	}
	
}

void ExplosionManager::draw()
{
	for (auto explosion : m_pExplosionPool)
	{
		if (explosion->isActive())
		{
			explosion->draw();

		}
	}
}

Explosion* ExplosionManager::getExplosion()
{
	Explosion* explosion = m_pExplosionPool.front();
	m_pExplosionPool.pop_front();
	m_pExplosionPool.push_back(explosion);
	explosion->isActive();
	return explosion;
}

ExplosionManager::ExplosionManager(): m_explosionNumber(20)
{
	m_buildExplosionPool();
}

ExplosionManager::~ExplosionManager()
= default;

void ExplosionManager::m_buildExplosionPool()
{

	m_pExplosionPool = std::list<Explosion*>();
	
	for (int i = 0; i < m_explosionNumber; ++i)
	{
		m_pExplosionPool.push_back(new Explosion());
		
	}

	
}
