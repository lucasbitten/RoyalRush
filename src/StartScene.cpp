#include "StartScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include <iomanip>

#include "GameManager.h"

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
				TheGame::Instance()->changeSceneState(SceneState::LEVEL2_SCENE);
				break;
			case SDLK_3:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL3_SCENE);
				break;
			case SDLK_4:
				TheGame::Instance()->changeSceneState(SceneState::LEVEL_COMPLETE_SCENE);
				break;
			case SDLK_5:
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
	TheGameManager::Instance()->reset();

	TheGameManager::Instance()->m_currentLevel = TheGame::Instance()->m_currentSceneState;

	
	TheSoundManager::Instance()->load("../Assets/audio/Music.mp3", "music", SOUND_MUSIC);
	TheSoundManager::Instance()->playMusic("music", 1);
	
	TheSoundManager::Instance()->load("../Assets/audio/lose.wav", "detected", SOUND_SFX);
	
	m_background = new Background();
	addChild(m_background);
	
	m_pStartButton = new StartButton();
	m_pStartButton->setPosition(glm::vec2(Config::SCREEN_WIDTH * 0.5f, 420.0f));
	addChild(m_pStartButton);


	SDL_Color white = { 255, 255, 255, 255 };
	m_pStartLabel = new Label("Royal Rush", "viking", 80, white,
		glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

}

glm::vec2 StartScene::getMousePosition()
{
	TheSoundManager::Instance()->load("../Assets/audio/door-01.flac", "dr", SOUND_SFX);

	return m_mousePosition;
}
