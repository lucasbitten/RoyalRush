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
	for (Ground* ground : m_pGrounds) {
		ground->draw();
	}
	for (Ground* ground : m_pGroundsVertical) {
		ground->draw();
	}
	m_pPlayer->draw();
	m_pEnemy->draw();
	
	for (Shadow* shadow : m_pShadows) {
		shadow->draw();
	}
}

void Level1Scene::moveEnemy()
{
	float x1 = m_pEnemy->getPosition().x;
	float x2 = m_pEnemy->getStartPos().x;
	float x3 = m_pEnemy->getEndPos().x;
	Move direction = m_pEnemy->getCurrentDirection();

	if(direction == Move::RIGHT)
	{
		m_pEnemy->move(Move::RIGHT);
		if(x1>x3)
		{
			m_pEnemy->setCurrentDirection(LEFT);
		}
	}
	else
	{
		m_pEnemy->move(Move::LEFT);
		if (x1 < x2)
		{
			m_pEnemy->setCurrentDirection(RIGHT);
		}
	}
}

void Level1Scene::update()
{

	for (Shadow* shadow: m_pShadows)
	{
		DetectShadowManager::playerOnShadow(shadow, m_pPlayer);
	}
	
	
	for (Ground* ground : m_pGrounds) {

		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

		bottomLine = glm::vec2(m_pEnemy->getPosition().x, m_pEnemy->getPosition().y + m_pEnemy->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pEnemy, bottomLine, ground, ground->getWidth(), ground->getHeight());
		
	}
	for (Ground* ground : m_pGroundsVertical) {
		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

		Collision::squaredRadiusCheckPlayer(m_pPlayer, ground);
		
	}
	if(CollisionManager::AABBCheckPlayer(m_pPlayer, m_pEnemy))
	{
		TheSoundManager::Instance()->playSound("yay", 0);
		std::cout << "Colided"<< std::endl;
		m_pPlayer->isCollidingEnemy = true;
		m_pEnemy->isCollidingPlayer = true;
	}
	else
	{
		m_pPlayer->isCollidingEnemy = false;
		m_pEnemy->isCollidingPlayer = false;
	}
	m_pEnemy->update();
	m_pPlayer->update();
	m_pPlayer->isGrounded = playerIsGrounded();
	if(!m_pEnemy->isCollidingPlayer)
	{
		moveEnemy();
	}
	//m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x * 0.1f, m_pPlayer->getVelocity().y));
	m_pPlayer->onShadow = playerIsOnShadow();
	//std::cout << "Player on shadow = " << m_pPlayer->onShadow << std::endl;
	bool isStartPointReached = false;

	//manage scrolling
	if(m_pPlayer->getPosition().x > frontScrollingPoint)
	{
		int i = 5;
		int count = 0;
		bool isEndPointReached = false;
		for (Ground* ground : m_pGrounds) {
			if(count == totalGroundElements -1)
			{
				if(ground->getPosition().x <= initialEndPoint)
				{
					float* tempXvalues = new float[totalGroundElements];
					float temp = 775;
					for(int i = totalGroundElements-1; i >= 0; i--)
					{
						tempXvalues[i] = temp;
						temp -= 50;
					}
					count = 0;
					for(Ground* ground : m_pGrounds)
					{
						ground->setPosition(glm::vec2(tempXvalues[count], 330));
						count++;
					}
					isEndPointReached = true;
					break;
				}
			}
			ground->setPosition(glm::vec2(ground->getPosition().x - i, 330));
			count++;
		}
		if (!isEndPointReached) {
			m_pPlayer->setPosition(glm::vec2(m_pPlayer->getPosition().x - i, m_pPlayer->getPosition().y));
			m_pEnemy->setPosition(glm::vec2(m_pEnemy->getPosition().x - i, m_pEnemy->getPosition().y));
			m_pEnemy->setStartPos(glm::vec2(m_pEnemy->getStartPos().x - i, m_pEnemy->getStartPos().y));
			m_pEnemy->setEndPos(glm::vec2(m_pEnemy->getEndPos().x - i, m_pEnemy->getEndPos().y));


			for (Shadow* shadow : m_pShadows) {
				shadow->setPosition(glm::vec2(shadow->getPosition().x - i, shadow->getPosition().y));
			}

			for (Ground* ground : m_pGroundsVertical) {
				ground->setPosition(glm::vec2(ground->getPosition().x - i, ground->getPosition().y));
			}
		}
	}
	if(m_pPlayer->getPosition().x < backScrollingPoint)
	{
		int i = 5;
		int count = 0;
		
		for (Ground* ground : m_pGrounds) {
			if (count == 0)
			{
				if (ground->getPosition().x >= initialStartPoint)
				{
					float temp = 25;
					
					for (Ground* ground : m_pGrounds)
					{
						ground->setPosition(glm::vec2(temp, 330));
						temp += 50;
					}
					isStartPointReached = true;
					break;
				}
			}
			ground->setPosition(glm::vec2(ground->getPosition().x + i, 330));
			count++;
		}
		if (!isStartPointReached) {
			for (Shadow* shadow : m_pShadows) {
				shadow->setPosition(glm::vec2(shadow->getPosition().x + i, shadow->getPosition().y));
			}

			m_pPlayer->setPosition(glm::vec2(m_pPlayer->getPosition().x + i, m_pPlayer->getPosition().y));
			m_pEnemy->setPosition(glm::vec2(m_pEnemy->getPosition().x + i, m_pEnemy->getPosition().y));
			m_pEnemy->setStartPos(glm::vec2(m_pEnemy->getStartPos().x + i, m_pEnemy->getStartPos().y));
			m_pEnemy->setEndPos(glm::vec2(m_pEnemy->getEndPos().x + i, m_pEnemy->getEndPos().y));

			for (Ground* ground : m_pGroundsVertical) {
				ground->setPosition(glm::vec2(ground->getPosition().x + i, ground->getPosition().y));
			}
		}
	}


	//set initial position and end position

	//if(gr)

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

	//sounds load

	TheSoundManager::Instance()->load("../Assets/audio/lose.wav", "yay", SOUND_SFX);
	TheSoundManager::Instance()->load("../Assets/audio/jing.ogg", "bg", SOUND_SFX);
	TheSoundManager::Instance()->playSound("bg", 1);

	
	backScrollingPoint = 150.0f;
	frontScrollingPoint = 650.0f;
	initialStartPoint = 0.0f;
	initialEndPoint = 800.0f;
	// allocates memory on the heap for this game object

	m_pPlayer = new Player();
	m_pEnemy = new Enemy();
	addChild(m_pPlayer);
	addChild(m_pEnemy);
	
	for (size_t i = 0; i < 1; i++)
	{
		m_pShadows.push_back(new Shadow());

	}

	for (Shadow* shadow : m_pShadows) {
		shadow->setPosition(glm::vec2(374, 265));
		addChild(shadow);
	}
	
	
	for (size_t i = 0; i < totalGroundElements; i++)
	{
		m_pGrounds.push_back(new Ground());

	}
	
	m_pPlayer->setPosition(glm::vec2(120, 150));
	m_pEnemy->setPosition(glm::vec2(420, 150));
	m_pEnemy->setStartPos(glm::vec2(400, 150));
	m_pEnemy->setEndPos(glm::vec2(500, 150));
	m_pEnemy->setCurrentDirection(Move::RIGHT);
	int i = 0;
	
	for (Ground* ground : m_pGrounds) {
		ground->setPosition(glm::vec2(80 + i, 330));
		addChild(ground);

		i += 50;
	}
	
	for (size_t i = 0; i < 3; i++)
	{
		m_pGroundsVertical.push_back(new Ground());
	}
	int j = 0;
	
	for (Ground* ground : m_pGroundsVertical) {
		ground->setPosition(glm::vec2(300,330 - j));
		addChild(ground);

		j += 50;
	}
}

glm::vec2 Level1Scene::getMousePosition()
{
	return m_mousePosition;
}