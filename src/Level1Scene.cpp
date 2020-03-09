#include "Level1Scene.h"
#include "Game.h"
#include <iostream>
#include "DetectShadowManager.h"

Level1Scene::Level1Scene()
{
	start();
}

Level1Scene::~Level1Scene()
{
}

void Level1Scene::draw()
{
	m_background.draw();
	for (Ground* ground : m_pGrounds) {
		ground->draw();
	}
	for (Ground* ground : m_pGroundsVertical) {
		ground->draw();
	}

	m_pFinishLevel->draw();

	
	m_pPlayer->draw();
	
	for (Enemy* enemy : m_pEnemy) {

		enemy->draw();
	}

	

	for (Shadow* shadow : m_pShadows) {
		shadow->draw();
	}

	
}


void Level1Scene::update()
{

	if (m_pPlayer->getPosition().x > m_pFinishLevel->getPosition().x + 50)
	{
		TheGame::Instance()->changeSceneState(SceneState::LEVEL_COMPLETE_SCENE);

	}

	for (Shadow* shadow: m_pShadows)
	{
		DetectShadowManager::playerOnShadow(shadow, m_pPlayer);
	}
	
	
	for (Ground* ground : m_pGrounds) {

		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

		for (Enemy* enemy : m_pEnemy) {
			bottomLine = glm::vec2(enemy->getPosition().x, enemy->getPosition().y + enemy->getHeight() / 2 + 22);
			Collision::lineRectCheck(enemy, bottomLine, ground, ground->getWidth(), ground->getHeight());
		}
		

		
	}
	for (Ground* ground : m_pGroundsVertical) {
		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

		Collision::squaredRadiusCheckPlayer(m_pPlayer, ground);
		
	}


	for (Enemy* enemy : m_pEnemy) {
		enemy->update();
		Collision::squaredRadiusCheck(m_pPlayer, enemy);
		enemy->detectPlayer(m_pPlayer);
	}
	



	
	m_pPlayer->update();
	m_pPlayer->isGrounded = playerIsGrounded();

	//m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x * 0.1f, m_pPlayer->getVelocity().y));
	m_pPlayer->onShadow = playerIsOnShadow();
	//std::cout << "Player on shadow = " << m_pPlayer->onShadow << std::endl;
	
}


bool Level1Scene::playerIsGrounded()
{
	for (Ground* ground : m_pGrounds) {

		if (ground->playerAtGround == true)
		{
			return true;
		}
	}

	for (Ground* ground : m_pGroundsVertical) {

		if (ground->playerAtGround == true)
		{
			return true;
		}
	}

	
	return false;
}


bool Level1Scene::playerIsOnShadow()
{
	for (Shadow* shadow : m_pShadows) {

		if (shadow->playerAtShadow == true)
		{
			return true;
		}
	}
	return false;
}


void Level1Scene::clean()
{
}

void Level1Scene::handleEvents()
{
	int wheel = 0;

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
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;
			}
		
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
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
				if (m_pPlayer->isGrounded)
				{
					m_pPlayer->jump();
					
				}
				break;
			case SDLK_s:
				
				break;
			case SDLK_a:
				m_pPlayer->move(LEFT);
				break;
			case SDLK_d:
				m_pPlayer->move(RIGHT);

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
	m_pFinishLevel = new FinishLevel();
	m_pFinishLevel->setPosition(glm::vec2(1300, 295));
	
	m_background = Background();
	
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	for (size_t i = 0; i < 3; i++)
	{
		m_pEnemy.push_back(new Enemy());
		
	}

	m_pEnemy[0]->setPosition(glm::vec2(400, 300));
	m_pEnemy[1]->setPosition(glm::vec2(770, 300));
	m_pEnemy[2]->setPosition(glm::vec2(1100, 300));

	m_pEnemy[0]->setSpeed(0.01);
	m_pEnemy[1]->setSpeed(0.009);
	m_pEnemy[2]->setSpeed(0.007);
	
	for (Enemy* enemy : m_pEnemy) {
		enemy->setRange();
	}

	m_pEnemy[2]->setPatrolRange(100);
	
	for (size_t i = 0; i < m_shadowNum; i++)
	{
		m_pShadows.push_back(new Shadow());
		
	}

	m_pShadows[0]->setPosition(glm::vec2(375, 265));
	m_pShadows[1]->setPosition(glm::vec2(675, 265));

	for (size_t i = 0; i < totalGroundElements; i++)
	{
		m_pGrounds.push_back(new Ground());

	}
	
	m_pPlayer->setPosition(glm::vec2(120, 150));

	int i = 0;
	
	for (Ground* ground : m_pGrounds) {
		ground->setPosition(glm::vec2(i, 330));
		addChild(ground);

		i += 50;
	}
	
	for (size_t i = 0; i < 7; i++)
	{
		m_pGroundsVertical.push_back(new Ground());
	}

	int j = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_pGroundsVertical[i]->setPosition(glm::vec2(300, 330 - j));
		j += 50;
	}
	j = 0;

	for (int i = 4; i < 7; ++i)
	{
		m_pGroundsVertical[i]->setPosition(glm::vec2(600, 330 - j));
		j += 50;
	}
	
	

}

glm::vec2 Level1Scene::getMousePosition()
{
	return m_mousePosition;
}