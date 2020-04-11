#pragma once
#ifndef __GAME_OVER_SCENE__
#define __GAME_OVER_SCENE__

#include "Background.h"
#include "Scene.h"
#include "Label.h"
#include "PlayAgain.h"

class GameOverScene : public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	glm::vec2 getMousePosition();
private:

	Background* m_background;

	glm::vec2 m_mousePosition;
	Label* m_Label;
	PlayAgain* m_pPlayAgain;
};

#endif /* defined (__END_SCENE__) */