#include "Level1Scene.h"
#include "Game.h"
#include <iostream>

Level1Scene::Level1Scene()
{
	start();
}

Level1Scene::~Level1Scene()
{
}

void Level1Scene::draw()
{
	m_pGround->draw();
	m_pPlayer->draw();
	m_pShadow->draw();
}

void Level1Scene::update()
{
	m_pPlayer->update();
	m_pStartButton->setMousePosition(m_mousePosition);
	m_pStartButton->ButtonClick();
	Collision::AABBCheckPlayer(m_pPlayer, m_pGround);
}

void Level1Scene::clean()
{
}

void Level1Scene::handleEvents()
{
	int wheel = 0;

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
			//m_pPlayer->setPosition(glm::vec2(m_mousePosition.x, m_mousePosition.y));
			/*std::cout << "Mouse X: " << m_mousePosition.x << std::endl;
			std::cout << "Mouse Y: " << m_mousePosition.y << std::endl;
			std::cout << "---------------------------------------------" << std::endl;*/
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button)
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
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			case SDLK_2:
				TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			

				/************************************************************************/
			case SDLK_w:
				m_pPlayer->jumping = true;
				break;
			case SDLK_s:
				
				break;
			case SDLK_a:
				m_pPlayer->setVelocity(glm::vec2(-10, m_pPlayer->getVelocity().y));

				break;
			case SDLK_d:
				m_pPlayer->setVelocity(glm::vec2(10, m_pPlayer->getVelocity().y));

				break;
			}
			
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				//m_pPlayer->jumping = false;

				break;

			case SDLK_s:
				
				break;

			case SDLK_a:
				m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));

				break;
			case SDLK_d:
				m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));

				break;
			}
			
			break;
		default:
			break;
		}
	}
}

void Level1Scene::start()
{
	// allocates memory on the heap for this game object
	m_pStartButton = new StartButton();
	m_pStartButton->setMouseButtonClicked(false);

	m_pPlayer = new Player();
	m_pShadow = new Shadow();
	m_pGround = new Ground();
	
	m_pPlayer->setPosition(glm::vec2(300, 300));
	m_pShadow->setPosition(glm::vec2(500, 300));
	m_pGround->setPosition(glm::vec2(300,330));
}

glm::vec2 Level1Scene::getMousePosition()
{
	return m_mousePosition;
}

/*
bool Level1Scene::m_MouseOver()
{
	float topLeftX = m_pStartButton->getPosition().x - m_pStartButton->getWidth() * 0.5;
	float topLeftY = m_pStartButton->getPosition().y - m_pStartButton->getHeight() * 0.5;
	float width = m_pStartButton->getWidth();
	float height = m_pStartButton->getHeight();

	
	if(m_mousePosition.x > topLeftX &&
		m_mousePosition.x < topLeftX + width &&
		m_mousePosition.y > topLeftY &&
		m_mousePosition.y < topLeftY + height)
	{
		//std::cout << "Mouse Over!!" << std::endl;

		m_pStartButton->setAlpha(178);
		return true;
	}
	else
	{
		m_pStartButton->setAlpha(255);
		return false;
	}
}

void Level1Scene::m_MouseClick()
{
	if(m_MouseOver() && m_mouseClicked)
	{
		std::cout << "Mouse Button Clicked!" << std::endl;
	}
}

*/
