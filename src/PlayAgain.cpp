#include "PlayAgain.h"
#include "Game.h"

PlayAgain::PlayAgain()
	:Button(
		"../Assets/textures/PlayAgain.png",
		"playAgain",
		START_BUTTON, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.5f)), m_isClicked(false)
{
	
}

PlayAgain::~PlayAgain()
{
}

bool PlayAgain::ButtonClick()
{
	if (m_mouseOver() && m_mouseButtonClicked)
	{
		if (!m_isClicked)
		{
			TheGame::Instance()->changeSceneState(TheGame::Instance()->m_currentLevel);
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
