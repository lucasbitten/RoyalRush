#pragma once
#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__
#include "Scene.h"
#include "SceneState.h"

class GameManager
{
public:
	static GameManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	SceneState m_currentLevel;
	int getPlayerLives() const;
	void setPlayerLives(int lives);

	void reset();

private:

	GameManager();
	~GameManager();

	static GameManager* s_pInstance;

	int m_playerLives = 3;
	Scene* m_currentScene{};

};

typedef GameManager TheGameManager;


#endif
