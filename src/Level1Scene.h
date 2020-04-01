#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

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


class Level1Scene : public Scene
{
public:
	Level1Scene();
	~Level1Scene();

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

	const int totalGroundElements = 35;
	int m_shadowNum = 2;
	std::vector<Shadow*> m_pShadows;

	std::vector<Ground*> m_pGrounds;
	std::vector<Ground*> m_pGroundsVertical;

	glm::vec2 m_mousePosition;


	std::vector<Enemy*> m_pEnemy;
};

#endif /* defined (__LEVEL1_SCENE__) */