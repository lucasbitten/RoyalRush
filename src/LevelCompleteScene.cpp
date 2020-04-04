#include "LevelCompleteScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>

LevelCompleteScene::LevelCompleteScene()
{
	LevelCompleteScene::start();
}

LevelCompleteScene::~LevelCompleteScene()
{
}

void LevelCompleteScene::draw()
{
	m_Label->draw();
	m_pPlayAgain->draw();
}

void LevelCompleteScene::update()
{
	m_pPlayAgain->setMousePosition(m_mousePosition);
	m_pPlayAgain->ButtonClick();
}

void LevelCompleteScene::clean()
{
	delete m_Label;
	removeAllChildren();
}

void LevelCompleteScene::handleEvents()
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

void LevelCompleteScene::start()
{
	SDL_Color blue = { 0, 0, 255, 255 };
	m_Label = new Label("Level Completed!", "Dock51", 50, blue, glm::vec2(Config::SCREEN_WIDTH * 0.5f, 200.0f));
	m_Label->setParent(this);
	addChild(m_Label);

	m_pPlayAgain = new PlayAgain();
	m_pPlayAgain->setParent(this);
	addChild(m_pPlayAgain);
}

glm::vec2 LevelCompleteScene::getMousePosition()
{
	return m_mousePosition;
}
