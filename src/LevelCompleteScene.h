#pragma once
#ifndef __LEVEL_COMPLETE_SCENE_
#define __LEVEL_COMPLETE_SCENE_

#include "Background.h"
#include "Scene.h"
#include "Label.h"
#include "PlayAgain.h"

class LevelCompleteScene : public Scene
{
public:
	LevelCompleteScene();
	~LevelCompleteScene();

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

#endif /* defined (__LEVEL_COMPLETE_SCENE_) */