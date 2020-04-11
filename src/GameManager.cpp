#include "GameManager.h"

GameManager* GameManager::s_pInstance = nullptr;

GameManager::GameManager()
= default;

GameManager::~GameManager()
= default;

int GameManager::getPlayerLives() const
{
	return m_playerLives;
}

void GameManager::setPlayerLives(int lives)
{
	m_playerLives = lives;
}

void GameManager::reset()
{
	m_playerLives = 3;

}