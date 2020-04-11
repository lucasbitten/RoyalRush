#pragma once
#ifndef __LEVEL2_SCENE__
#define __LEVEL2_SCENE__

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


class Level2Scene : public Scene
{
public:
	Level2Scene();
	~Level2Scene();

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
	Door* m_pFinishLevel;
	Key* m_pKey;

	bool isKeyPickedUp;
	
	const int totalGroundElements = 79;
	int m_shadowNum = 3;
	std::vector<Shadow*> m_pShadows;

	std::vector<Ground*> m_pGrounds;
	std::vector<GroundPlatform*> m_pGroundPlatforms;
	std::vector<Heart*> m_pPlayerLives;

	glm::vec2 m_mousePosition;


	std::vector<Enemy*> m_pEnemy;

};

#endif /* defined (__LEVEL1_SCENE__) */