#pragma once
#ifndef __LEVEL_1_SCENE__
#define __LEVEL_1_SCENE__

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
	
	void draw() override;
	void update() override;
	void clean() override;
	void handleEvents() override;
	void start() override;

	// getters
	glm::vec2 getMousePosition();

	bool playerIsOnShadow();
	bool playerIsGrounded();

	
private:
	// game objects
	Background m_background;
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

#endif /* defined (__LEVEL_1_SCENE__) */
