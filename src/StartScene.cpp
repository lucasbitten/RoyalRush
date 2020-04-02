#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
{
}

void StartScene::draw()
{
	drawDisplayList();


}

void StartScene::update()
{

	m_pStartButton->setMousePosition(m_mousePosition);
	m_pStartButton->ButtonClick();

	TheSoundManager::Instance()->load("../Assets/audio/door-01.flac", "dr", SOUND_SFX);

	//if(m_pStartButton->ButtonClick())
	//{
	//	TheSoundManager::Instance()->playSound("dr", 0);

	//}
}

void StartScene::clean()
{
	delete m_pStartLabel;
	delete m_pStartButton;
	
	removeAllChildren();
}

void StartScene::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
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
			std::cout << "click" << std::endl;
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(true);
				break;
			}

			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				m_pStartButton->setMouseButtonClicked(false);
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
				TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

// this function is used for initialization
void StartScene::start()
{
	m_pStartButton = new StartButton();
	addChild(m_pStartButton);


	SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("Royal Rush", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH * 0.5f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

}

glm::vec2 StartScene::getMousePosition()
{
	return m_mousePosition;
}
