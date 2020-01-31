#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"

// Game Objects
#include "ship.h"
#include "Target.h"
#include "Tile.h"
#include "Label.h"
#include "Planet.h"
#include "Mine.h"

#include <memory>

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	// Steering related functions
	glm::vec2 getTargetPosition();
	void setTargetPosition(glm::vec2 newPosition);

	// Pathfinding functions
	Tile* getTile(int col, int row);


	glm::vec2 getGoalLocation();
	void setGoalLocation(glm::vec2 newLocation);
	bool findShortestPath();
	void resetClosedAndOpen();
private:
	// GameObjects
	Ship m_ship;
	std::vector<Mine> m_pMines;
	Target m_pTarget;
	Label* m_pLabel;
	Planet m_planet;

	// utility functions for ship control
	void m_createShips();
	void m_drawShips();
	void m_updateShips();
	void m_respawnShips();
	void m_moveShipsAlongPath();

	// utility functions for planet control
	void m_createPlanet();
	void m_respawnPlanet();

	// utility functions for mine control
	void m_createMines();
	void m_drawMines();
	void m_updateMines();
	void m_respawnMines();

	// Tile and Grid variables
	const int m_rowSize = Config::ROW_NUM;
	const int m_colSize = Config::COL_NUM;
	const int m_tileSize = Config::TILE_SIZE;

	Tile* m_grid[Config::COL_NUM ][Config::ROW_NUM]; 

	glm::vec2 m_goalLocation;
	bool m_moveAlongPath = false;
	int m_pathLength = 0;

	std::vector<Tile* > m_pOpen;
	std::vector<Tile* > m_pClosed;

	// utility functions for tile and grid
	void m_createGrid();
	void m_drawGrid();
	void m_updateGrid();
	bool m_debugMode = false;
	Tile* m_getRandomEmptyTile();
	void m_assignNeighbours();

	glm::vec2 m_mousePosition;

	// ImGui utility functions
	void m_ImGuiKeyMap();
	void m_ImGuiSetStyle();
	void m_updateUI();

	// ImGui menu variables
	bool m_exitApp = false;
	bool m_displayAbout = false;
	bool m_displayUI = true;
	
	void m_resetAll();

};

#endif /* defined (__PLAY_SCENE__) */