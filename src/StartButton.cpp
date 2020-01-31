#include "StartButton.h"
#include "Game.h"

StartButton::StartButton()
	// call super constructor
	:Button(
		"../Assets/textures/StartButton.png",
		"startButton",
		START_BUTTON, glm::vec2(400.0f, 300.0f)), m_isClicked(false)
{
	
}

StartButton::~StartButton()
{
}

bool StartButton::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if(!m_isClicked)
		{
			std::cout << "Mouse Button Clicked!" << std::endl;
			m_isClicked = true;
		}
		return true;
	}
	else
	{
		m_isClicked = false;
	}

	return false;
}


