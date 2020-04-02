#include "Level1Scene.h"

#include "DetectShadowManager.h"
#include "Game.h"

Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	drawDisplayList();
	//ExplosionManager::Instance()->draw();

	
}

void Level1Scene::update()
{
	updateDisplayList();
	
	//ExplosionManager::Instance()->update();

	if (m_pPlayer->getPosition().x > m_pFinishLevel->getPosition().x + 50)
	{
		TheGame::Instance()->changeSceneState(SceneState::LEVEL_COMPLETE_SCENE);

	}

	for (Shadow* shadow : m_pShadows)
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
		Collision::squaredRadiusCheck(m_pPlayer, enemy);
		enemy->detectPlayer(m_pPlayer);
		if(Collision::squaredRadiusCheck(m_pPlayer, enemy))
		{
			TheSoundManager::Instance()->playSound("yay", 0);
		}

	}





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
	delete m_pFinishLevel;
	delete m_background;

	for (Ground* ground : m_pGrounds) {

		delete ground;
	}

	for (Ground* ground : m_pGroundsVertical) {

		delete ground;

	}

	for (Enemy* enemy : m_pEnemy) {
		delete enemy;
	}

	for (Shadow* shadow : m_pShadows) {
		delete shadow;
	}
	
	delete m_pPlayer;
	
	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
	
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
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//{
			//auto explosion = ExplosionManager::Instance()->getExplosion();
			//explosion->activate();
			//explosion->setPosition(m_mousePosition);
			//}
			break;
		case SDL_KEYDOWN:
			keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			// movement keys
			{
				if(keyPressed == SDLK_w)
				{
					if (m_pPlayer->isGrounded)
					{
						m_pPlayer->jump();

					}
				}

				if (keyPressed == SDLK_a)
				{
					//std::cout << "move left" << std::endl;
					m_pPlayer->move(LEFT);
					m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				}

				if (keyPressed == SDLK_s)
				{
					std::cout << "move back" << std::endl;
				
				}

				if (keyPressed == SDLK_d)
				{
					//std::cout << "move right" << std::endl;
					m_pPlayer->move(RIGHT);
					m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				}
			}
			
			break;
		case SDL_KEYUP:
			keyReleased = event.key.keysym.sym;

			if (keyReleased == SDLK_a)
			{
				m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));

				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}

			if (keyReleased == SDLK_d)
			{
				m_pPlayer->setVelocity(glm::vec2(0, m_pPlayer->getVelocity().y));

				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			break;
			
		}
	}
}

void Level1Scene::start()
{
	//sounds add
	TheSoundManager::Instance()->load("../Assets/audio/lose.wav", "yay", SOUND_SFX);

	TheSoundManager::Instance()->load("../Assets/audio/jing.ogg", "bg", SOUND_SFX);
	TheSoundManager::Instance()->playSound("bg", 1);

	// allocates memory on the heap for this game object


	m_background = new Background();
	addChild(m_background);


	int j = 0;

	for (size_t i = 0; i < totalGroundElements; i++)
	{
		auto ground = new Ground();
		m_pGrounds.push_back(ground);
		addChild(ground);
		ground->setPosition(glm::vec2(j, 330));
		j += 50;

	}


	for (size_t i = 0; i < 7; i++)
	{
		auto ground = new Ground();
		m_pGroundsVertical.push_back(ground);
		addChild(ground);
	}

	j = 0;

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


	m_pFinishLevel = new FinishLevel();
	m_pFinishLevel->setPosition(glm::vec2(1300, 295));
	addChild(m_pFinishLevel);
	
	m_pPlayer = new Player();
	m_pPlayer->setPosition(glm::vec2(120, 150));

	addChild(m_pPlayer);

	for (size_t i = 0; i < 3; i++)
	{
		auto enemy = new Enemy();
		m_pEnemy.push_back(enemy);
		addChild(enemy);

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
		auto shadow = new Shadow();
		m_pShadows.push_back(shadow);
		addChild(shadow);

	}

	m_pShadows[0]->setPosition(glm::vec2(375, 265));
	m_pShadows[1]->setPosition(glm::vec2(675, 265));


}
