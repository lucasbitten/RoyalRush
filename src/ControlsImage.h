#pragma once
#ifndef __CONTROLS_IMAGE__
#define __CONTROLS_IMAGE__

#include "DisplayObject.h"
#include <SDL_hints.h>

class ControlsImage : public DisplayObject
{
public:
	ControlsImage(std::string imagePath = "../Assets/textures/controls.png",
		std::string imageName = "controlsInfo",
		GameObjectType type = CONTROLS_IMAGE,
		glm::vec2 position = glm::vec2(0.0f, 0.0f), bool isCentered = true);

	virtual ~ControlsImage();

	void draw() override;
	void update() override;
	void clean() override;


private:
	Uint8 m_alpha;
	std::string m_name;
	bool m_isCentered;
};

#endif /* defined (__CONTROLS_IMAGE__) */