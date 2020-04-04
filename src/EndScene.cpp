#include "EndScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>
#include "SoundManager.h"

EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
{
}

void EndScene::draw()
{
	m_background->draw();
	m_Label->draw();
	m_pPlayAgain->draw();
}

void EndScene::update()
{
	m_pPlayAgain->setMousePosition(m_mousePosition);
	m_pPlayAgain->ButtonClick();
}

void EndScene::clean()
{
	delete m_Label;
	removeAllChildren();
}

void EndScene::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			/*std::cout << "Mouse X: " << m_mousePosition.x << std::endl;
			std::cout << "Mouse Y: " << m_mousePosition.y << std::endl;
			std::cout << "---------------------------------------------" << std::endl;*/
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pPlayAgain->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pPlayAgain->setMouseButtonClicked(false);
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				break;
			case SDLK_2:
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void EndScene::start()
{
	m_background = new Background();
	addChild(m_background);
	
	SDL_Color white = { 255, 255, 255, 255 };
	m_Label = new Label("OH, NO! YOU HAVE BEEN SPOTTED!", "viking", 45, white, glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f));
	m_Label->setParent(this);
	addChild(m_Label);

	m_pPlayAgain = new PlayAgain();
	m_pPlayAgain->setParent(this);
	m_pPlayAgain->setPosition(glm::vec2(Config::SCREEN_WIDTH * 0.5f, 420.0f));

	addChild(m_pPlayAgain);
}

glm::vec2 EndScene::getMousePosition()
{
	return m_mousePosition;
}
