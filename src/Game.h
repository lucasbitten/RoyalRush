#pragma once
#ifndef __GAME__
#define __GAME__

// Core Libraries
#include <iostream>
#include <string>
#include <vector>
#include "SceneState.h"

#include <SDL.h>

// IMGUI Includes
#include "IMGUI/imgui.h"

// Game Managers
#include "CollisionManager.h"

// Scenes
#include "StartScene.h"
#include "Level1Scene.h"
#include "EndScene.h"

#include "Config.h"

class Game
{
public:
	
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	// simply set the running variable to true
	void init() { m_bRunning = true; }

	bool init(const char* title, int x, int y, int width, int height, bool fullscreen);

	// public functions
	void render() const;
	void update() const;
	void handleEvents();
	void clean() const;

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	// getters
	SDL_Renderer* getRenderer() const;
	glm::vec2 getMousePosition() const;

	void setFrames(Uint32 frames);
	Uint32 getFrames() const;

	void changeSceneState(SceneState new_state);
	void quit();

	
private:
	Game();
	~Game();

	std::shared_ptr<SDL_Window> m_pWindow;

	std::shared_ptr<SDL_Renderer> m_pRenderer;

	int m_currentFrame;

	bool m_bRunning;

	static Game* s_pInstance;
	
	void start();

	glm::vec2 m_mousePosition;

	Uint32 m_frames;

	Scene* m_currentScene;
	SceneState m_currentSceneState;
};

typedef Game TheGame;

#endif /* defined (__GAME__) */

