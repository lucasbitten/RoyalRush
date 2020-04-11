#pragma once
#ifndef __LEVEL3_SCENE__
#define __LEVEL3_SCENE__

#include "Scene.h"


#include "Player.h"
#include "ExplosionManager.h"
#include "Scene.h"
#include "Player.h"
#include  "Shadow.h"
#include "Ground.h"
#include "Enemy.h"
#include "Background.h"
#include "FinishLevel.h"
#include "GroundPlatform.h"
#include "ControlsImage.h"
#include "TutorialInfo.h"
#include "Key.h"
#include "Door.h"
#include "Heart.h"


class Level3Scene : public Scene
{
public:
	Level3Scene();
	~Level3Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	glm::vec2 getMousePosition();

	bool playerIsOnShadow();
	bool playerIsGrounded();

private:

	Background* m_background;
	Player* m_pPlayer;
	FinishLevel* m_pFinishLevel;

	
	const int totalGroundElements = 60;
	int m_shadowNum = 3;
	std::vector<Shadow*> m_pShadows;

	std::vector<Ground*> m_pGrounds;
	std::vector<GroundPlatform*> m_pGroundPlatforms;

	glm::vec2 m_mousePosition;

	std::vector<Heart*> m_pPlayerLives;


	std::vector<Enemy*> m_pEnemy;

};

#endif /* defined (__LEVEL3_SCENE__) */