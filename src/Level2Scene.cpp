#include "Level2Scene.h"
#include "Game.h"
#include "DetectShadowManager.h"

Level2Scene::Level2Scene()
{
	Level2Scene::start();
}

Level2Scene::~Level2Scene()
{
}

void Level2Scene::draw()
{
	drawDisplayList();
	if(!isKeyPickedUp)
	{
		m_pKey->draw();
	}
}

void Level2Scene::update()
{
	updateDisplayList();
	if (isKeyPickedUp)
	{
		if (Collision::AABBCheckPlayer(m_pPlayer, m_pFinishLevel))
		{
			TheGame::Instance()->changeSceneState(LEVEL3_SCENE);
			return;
		}
	}

	//ExplosionManager::Instance()->update();

	for (Shadow* shadow : m_pShadows)
	{
		DetectShadowManager::playerOnShadow(shadow, m_pPlayer);
	}

	for (Ground* ground : m_pGrounds) {

		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2 + 22);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

	}

	for (GroundPlatform* ground : m_pGroundPlatforms) {
		auto bottomLine = glm::vec2(m_pPlayer->getPosition().x, m_pPlayer->getPosition().y + m_pPlayer->getHeight() / 2);
		Collision::lineRectCheck(m_pPlayer, bottomLine, ground, ground->getWidth(), ground->getHeight());

		Collision::squaredRadiusCheckPlayer(m_pPlayer, ground);

	}

	for (Enemy* enemy : m_pEnemy) {
		Collision::squaredRadiusCheck(m_pPlayer, enemy);
		if (enemy->detectPlayer(m_pPlayer))
		{
			TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
			return;
		}
		if (Collision::squaredRadiusCheck(m_pPlayer, enemy))
		{
			TheSoundManager::Instance()->playSound("yay", 0);
		}

	}

	if (!isKeyPickedUp) {
		if (Collision::AABBCheckPlayer(m_pPlayer, m_pKey))
		{
			TheSoundManager::Instance()->playSound("eg",0);
			isKeyPickedUp = true;
		}
	}

	m_pPlayer->isGrounded = playerIsGrounded();

	//m_pPlayer->setVelocity(glm::vec2(m_pPlayer->getVelocity().x * 0.1f, m_pPlayer->getVelocity().y));
	m_pPlayer->onShadow = playerIsOnShadow();
	//std::cout << "Player on shadow = " << m_pPlayer->onShadow << std::endl;

}

void Level2Scene::clean()
{
	delete m_pFinishLevel;
	delete m_background;

	for (Ground* ground : m_pGrounds) {

		delete ground;
	}

	for (GroundPlatform* ground : m_pGroundPlatforms) {

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

void Level2Scene::handleEvents()
{
	auto wheel = 0;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;

	SDL_Event event;


	const Uint8* state = SDL_GetKeyboardState(NULL);

	/*if (state[SDL_SCANCODE_S]) {

	}*/

	if (state[SDL_SCANCODE_W]) {
		if (m_pPlayer->isGrounded)
		{
			m_pPlayer->jump();

		}
	}

	if (state[SDL_SCANCODE_A]) {
		m_pPlayer->move(LEFT);
		m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
	}

	if (state[SDL_SCANCODE_D]) {
		m_pPlayer->move(RIGHT);
		m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
	}



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
			default:;
			}
			// movement keys
			//{
			//	if(keyPressed == SDLK_w)
			//	{
			//		if (m_pPlayer->isGrounded)
			//		{
			//			m_pPlayer->jump();

			//		}
			//	}

			//	if (keyPressed == SDLK_a)
			//	{
			//		//std::cout << "move left" << std::endl;
			//		m_pPlayer->move(LEFT);
			//		m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			//	}

			//	if (keyPressed == SDLK_s)
			//	{
			//		std::cout << "move back" << std::endl;
			//	
			//	}

			//	if (keyPressed == SDLK_d)
			//	{
			//		//std::cout << "move right" << std::endl;
			//		m_pPlayer->move(RIGHT);
			//		m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			//	}
			//}

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
		default:;
		}
	}
}

void Level2Scene::start()
{
	TheGame::Instance()->m_currentLevel = TheGame::Instance()->m_currentSceneState;

	TheSoundManager::Instance()->load("../Assets/audio/key.wav", "eg", SOUND_SFX);
	TheSoundManager::Instance()->load("../Assets/audio/key.wav", "eg", SOUND_SFX);
	//TheSoundManager::Instance()->playSound("eg", 1);

	
	m_background = new Background();
	addChild(m_background);

	for (size_t i = 0; i < 3; i++)
	{
		auto ground = new GroundPlatform();
		m_pGroundPlatforms.push_back(ground);
		addChild(ground);
	}

	m_pGroundPlatforms[0]->setPosition(glm::vec2(150, 490));
	m_pGroundPlatforms[1]->setPosition(glm::vec2(400, 490));
	m_pGroundPlatforms[2]->setPosition(glm::vec2(800, 490));


	int j = 0;
	int k = 550;
	for (int i = 0; i < totalGroundElements; i++)
	{
		auto ground = new Ground();
		m_pGrounds.push_back(ground);
		addChild(ground);
		if(i==55)
		{
			k = 320;
			j = 850;
		}
		if(i==60)
		{
			k = 200;
			j = 0;
		}
		if(i==65)
		{
			//k = 70;
			j = 280;
		}
		if (i == 70)
		{
			//k = 70;
			j = 530;
		}
		ground->setPosition(glm::vec2(j, k));
		j += 32;

	}

	m_pFinishLevel = new Door();
	m_pFinishLevel->setPosition(glm::vec2(1380, 460));
	addChild(m_pFinishLevel);

	m_pKey = new Key();
	m_pKey->setPosition(glm::vec2(35, 160));

	// Player
	m_pPlayer = new Player();
	m_pPlayer->setPosition(glm::vec2(30, 505));
	addChild(m_pPlayer);

	// Enemies
	for (size_t i = 0; i < 4; i++)
	{
		auto enemy = new Enemy();
		m_pEnemy.push_back(enemy);
		addChild(enemy);

	}
	// Enemies positions
	m_pEnemy[0]->setPosition(glm::vec2(600, 515));
	m_pEnemy[1]->setPosition(glm::vec2(970, 515));
	m_pEnemy[2]->setPosition(glm::vec2(1100, 515));
	m_pEnemy[3]->setPosition(glm::vec2(290, 515));

	for (auto enemy : m_pEnemy) {
		enemy->setRange();
	}
	m_pEnemy[0]->setPatrolRange(120);
	m_pEnemy[1]->setPatrolRange(120);
	m_pEnemy[2]->setPatrolRange(100);
	m_pEnemy[3]->setPatrolRange(60);

	// Shadows
	for (size_t i = 0; i < m_shadowNum; i++)
	{
		auto shadow = new Shadow();
		m_pShadows.push_back(shadow);
		addChild(shadow);

	}
	// Shadows Positions
	m_pShadows[0]->setPosition(glm::vec2(245, 485));
	m_pShadows[1]->setPosition(glm::vec2(495, 485));
	m_pShadows[2]->setPosition(glm::vec2(895, 485));

	isKeyPickedUp = false;
}
bool Level2Scene::playerIsOnShadow()
{
	for (Shadow* shadow : m_pShadows) {

		if (shadow->playerAtShadow == true)
		{
			return true;
		}
	}
	return false;
}

bool Level2Scene::playerIsGrounded()
{
	for (Ground* ground : m_pGrounds) {

		if (ground->playerAtGround == true)
		{
			return true;
		}
	}

	for (GroundPlatform* ground : m_pGroundPlatforms) {

		if (ground->playerAtGround == true)
		{
			return true;
		}
	}


	return false;
}
