#pragma once
#ifndef __LEVEL_1_SCENE__
#define __LEVEL_1_SCENE__

#include "Scene.h"
#include "StartButton.h"
#include "Player.h"
#include  "Shadow.h"
#include "Ground.h"

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

private:
	// game objects

	glm::vec2 m_mousePosition;
	
	StartButton* m_pStartButton;

	Player* m_pPlayer;

	Shadow* m_pShadow;

	Ground* m_pGround;
};

#endif /* defined (__LEVEL_1_SCENE__) */
