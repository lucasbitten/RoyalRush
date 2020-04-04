#pragma once
#ifndef __TUTORIAL_INFO__
#define __TUTORIAL_INFO__

#include "DisplayObject.h"
#include <SDL_hints.h>

class TutorialInfo : public DisplayObject
{
public:
	TutorialInfo(std::string imagePath = "../Assets/textures/shadow-info.png",
		std::string imageName = "shadowInfo",
		GameObjectType type = SHADOW_INFO,
		glm::vec2 position = glm::vec2(0.0f, 0.0f), bool isCentered = true);

	virtual ~TutorialInfo();

	void draw() override;
	void update() override;
	void clean() override;


private:
	Uint8 m_alpha;
	std::string m_name;
	bool m_isCentered;
};

#endif /* defined (__TUTORIAL_INFO__) */