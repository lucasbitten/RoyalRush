#include "PlayScene.h"
#include "Game.h"
#include <ctime>
#include "GLM/gtx/string_cast.hpp"
#include <algorithm>
#include "TileComparators.h"
#include <iomanip>


// Pathfinding & Steering functions ***********************************************

glm::vec2 PlayScene::getTargetPosition()
{
	return m_pTarget.getPosition();
}

void PlayScene::setTargetPosition(glm::vec2 newPosition)
{
	m_pTarget.setPosition(newPosition);
}

Tile * PlayScene::getTile(int col, int row)
{
	return m_grid[col][row];
}

glm::vec2 PlayScene::getGoalLocation()
{
	return m_goalLocation;
}

void PlayScene::setGoalLocation(glm::vec2 newLocation)
{
	m_goalLocation = newLocation;

	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_grid[col][row]->setTargetDistance(m_goalLocation);
		}
	}
}

bool PlayScene::findShortestPath()
{
	// reset tiles
	resetClosedAndOpen();

	Tile* currentTile = m_ship.getTile();
	currentTile->setTileState(TileState::CLOSED);
	currentTile->setTileStateLabel("C");
	m_pClosed.push_back(currentTile);

	int pathlength = 0;
	while (currentTile->getTileState() != TileState::GOAL)
	{
		std::vector<Tile*> adjacentTiles;
		int openAdjacentTiles = 0;

		if (currentTile->getGridPosition().y != 0) {
			if (currentTile->up()->getTileState() != TileState::CLOSED)
			{
				adjacentTiles.push_back(currentTile->up());
			}
		}

		if (currentTile->getGridPosition().y != Config::ROW_NUM - 1)
		{
			if (currentTile->down()->getTileState() != TileState::CLOSED)
			{
				adjacentTiles.push_back(currentTile->down());
			}
		}

		if (currentTile->getGridPosition().x != Config::COL_NUM - 1)
		{
			if (currentTile->right()->getTileState() != TileState::CLOSED)
			{
				adjacentTiles.push_back(currentTile->right());
			}
		}

		if (currentTile->getGridPosition().x != 0)
		{
			if (currentTile->left()->getTileState() != TileState::CLOSED)
			{
				adjacentTiles.push_back(currentTile->left());
			}
		}

		if (adjacentTiles.size() == 0)
		{
			//std::cout << "Dead Path" << std::endl;
			return false;
		}

		std::sort(adjacentTiles.begin(), adjacentTiles.end(), ComparatorByValue());

		//std::cout << "next tile ******************************************************" << std::endl;
		for (size_t i = 0; i < adjacentTiles.size(); i++)
		{
			//std::cout << "tilestate: " << adjacentTiles[i]->getTileState() << " - ";
			if (i == 0)
			{
				currentTile = adjacentTiles[i];
				m_pOpen.push_back(adjacentTiles[i]);

				if (adjacentTiles[i]->getTileState() != TileState::GOAL)
				{
					currentTile->setTileStateLabel("O");
					adjacentTiles[i]->setTileState(TileState::CLOSED);
				}

				//std::cout << "value chosen: " << std::fixed << std::setprecision(1) << adjacentTiles[i]->getTileValue() << " - " << adjacentTiles[i]->getPosition().x << "," << adjacentTiles[i]->getPosition().y << std::endl;
			}
			else
			{
				adjacentTiles[i]->setTileState(TileState::CLOSED);
				adjacentTiles[i]->setTileStateLabel("C");
				m_pClosed.push_back(adjacentTiles[i]);
				//std::cout << "value ignored: " << std::fixed << std::setprecision(1) << adjacentTiles[i]->getTileValue() << " - " << adjacentTiles[i]->getPosition().x << "," << adjacentTiles[i]->getPosition().y << std::endl;
			}
		}
		adjacentTiles.clear();

		// ensure a dead end actually ends

		//std::cout << " path length: " << pathlength << " ***********************************************" << std::endl;
		pathlength++;
	}

	return true;

}

void PlayScene::resetClosedAndOpen()
{
	// reset tiles
	for (Tile* tile : m_pClosed)
	{
		tile->setTileState(TileState::OPEN);
		tile->setTileStateLabel("-");
	}

	m_pClosed.clear();

	for (Tile* tile : m_pOpen)
	{
		tile->setTileState(TileState::OPEN);
		tile->setTileStateLabel("-");
	}
	m_pOpen.clear();
}

// Ship functions ***********************************************

void PlayScene::m_createShips()
{
	m_ship = Ship();
	m_ship.setParent(this);
	addChild(&m_ship);
	m_respawnShips();
}

void PlayScene::m_drawShips()
{
	m_ship.draw();
}

void PlayScene::m_updateShips()
{
	m_ship.setTarget(m_pTarget.getPosition());
	m_ship.update();
}

void PlayScene::m_respawnShips()
{
	resetClosedAndOpen();


	if (m_ship.getTile() != NULL)
	{
		if (m_ship.getTile()->getTileState() != TileState::GOAL) {
			m_ship.getTile()->setTileState(TileState::OPEN);
			m_ship.getTile()->setTileStateLabel("-");
		}
	}

	Tile* tile = m_getRandomEmptyTile();

		
	//std::cout << "m_Ship initial position: " << glm::to_string(m_ship.getPosition()) << std::endl;


	m_ship.setPosition(tile->getPosition());

	//std::cout << "m_Ship altered position: " << glm::to_string(m_ship.getPosition()) << std::endl;

	m_pTarget.setPosition(m_ship.getPosition());

	//std::cout << "target altered position: " << glm::to_string(m_pTarget.getPosition()) << std::endl;

	tile->setTileState(TileState::START);
	tile->setTileStateLabel("S");
	m_ship.setTile(tile);

}

void PlayScene::m_moveShipsAlongPath()
{
	if (TheGame::Instance()->getFrames() % 20 == 0)
	{
		if (m_pathLength < m_pOpen.size())
		{
			m_pTarget.setPosition(m_pOpen[m_pathLength]->getPosition());
			m_ship.setTile(m_pOpen[m_pathLength]);
			m_pathLength++;
		}
		else
		{
			m_moveAlongPath = false;
		}
	}
}

// Planet functions ***********************************************

void PlayScene::m_createPlanet()
{
	m_planet = Planet();
	m_planet.setParent(this);
	addChild(&m_planet);
	m_respawnPlanet();
}

void PlayScene::m_respawnPlanet()
{
	resetClosedAndOpen();

	if (m_planet.getTile() != NULL)
	{
		m_planet.getTile()->setTileState(TileState::OPEN);
		m_planet.getTile()->setTileStateLabel("-");
	}

	Tile* tile = m_getRandomEmptyTile();

	m_planet.setTile(tile);
	m_planet.setPosition(tile->getPosition());
	tile->setTileState(TileState::GOAL);
	tile->setTileStateLabel("G");

	setGoalLocation(glm::vec2(tile->getGridPosition().x, tile->getGridPosition().y));
}

// Mine functions ***********************************************

void PlayScene::m_createMines()
{
	for (size_t count = 0; count < Config::MINE_NUM; count++)
	{
		Mine newMine = Mine();
		m_pMines.push_back(newMine);
		newMine.setParent(this);
		addChild(&newMine);
	}

	m_respawnMines();
}

void PlayScene::m_drawMines()
{
	for (Mine mine : m_pMines)
	{
		mine.draw();
	}
}

void PlayScene::m_updateMines()
{
	for (Mine mine : m_pMines)
	{
		mine.update();
	}
}

void PlayScene::m_respawnMines()
{

	for (size_t mine_index = 0; mine_index < Config::MINE_NUM; mine_index++)
	{
		if (m_pMines[mine_index].getTile() != NULL)
		{
			m_pMines[mine_index].getTile()->setTileState(TileState::OPEN);
		}

		Tile* tile = m_getRandomEmptyTile();
		m_pMines[mine_index].setPosition(tile->getPosition());
		tile->setTileState(TileState::CLOSED);
		m_pMines[mine_index].setTile(tile);
	}
}

// Grid functions ***********************************************

void PlayScene::m_assignNeighbours()
{
	// assign neighbours
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			if (row != 0) {
				m_grid[col][row]->setUp(m_grid[col][row - 1]);
			}
			else
			{
				m_grid[col][row]->setUp(NULL);
			}

			

			if (col != Config::COL_NUM - 1) {
				m_grid[col][row]->setRight(m_grid[col + 1][row]);
			}
			else
			{
				m_grid[col][row]->setRight(NULL);
			}

			if (row != Config::ROW_NUM - 1) {
				m_grid[col][row]->setDown(m_grid[col][row + 1]);
			}
			else
			{
				m_grid[col][row]->setDown(NULL);
			}

			if (col != 0) {
				m_grid[col][row]->setLeft(m_grid[col - 1][row]);
			}
			else
			{
				m_grid[col][row]->setLeft(NULL);
			}

		}
	}
}

void PlayScene::m_createGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			float rowPosition = row * m_tileSize + 20.0f;
			float colPosition = col * m_tileSize + 20.0f;
			m_grid[col][row] = new Tile(glm::vec2(colPosition, rowPosition), glm::vec2(col, row));
			m_grid[col][row]->setParent(this);
			addChild(m_grid[col][row]);
		}
	}

	m_assignNeighbours();
}

void PlayScene::m_drawGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_grid[col][row]->draw();
		}
	}
}

void PlayScene::m_updateGrid()
{
	for (size_t row = 0; row < m_rowSize; row++)
	{
		for (size_t col = 0; col < m_colSize; col++)
		{
			m_grid[col][row]->update();
		}
	}
}

Tile * PlayScene::m_getRandomEmptyTile()
{
	int randomRow;
	int randomCol;
	do
	{
		randomRow = rand() % m_rowSize;
		randomCol = rand() % m_colSize;
	} while (m_grid[randomCol][randomRow]->getTileState() != TileState::OPEN);
	return m_grid[randomCol][randomRow];
}

// ImGui functions ***********************************************

void PlayScene::m_ImGuiKeyMap()
{
	ImGuiIO& io = ImGui::GetIO();

	// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
	io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
	io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
	io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;

	io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
	io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
	io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
	io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
	io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
	io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;
}

void PlayScene::m_ImGuiSetStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 0.8f;
	style.FrameRounding = 3.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void PlayScene::m_updateUI()
{
	// Prepare Window Frame
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow(); // use for debug purposes

	std::string windowString = "Settings ";

	ImGui::Begin(&windowString[0], NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);

	// set window to top left corner
	ImGui::SetWindowPos(ImVec2(0, 0), true);

	/*************************************************************************************************/
	/* MENU                                                                                          */
	/*************************************************************************************************/

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::Separator();
			ImGui::MenuItem("Exit", NULL, &m_exitApp);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::Separator();
			ImGui::MenuItem("About", NULL, &m_displayAbout);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (m_exitApp)
	{
		TheGame::Instance()->quit();
	}

	if (m_displayAbout)
	{
		ImGui::Begin("About Pathfinding Simulator", &m_displayAbout, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Separator();
		ImGui::Text("Authors:");
		ImGui::Text("Tom Tsiliopoulos ");
		ImGui::End();
	}

	/*************************************************************************************************/
	if (ImGui::Button("Respawn Ships"))
	{
		m_respawnShips();
		m_moveAlongPath = false;
	}

	ImGui::SameLine();

	if (ImGui::Button("Respawn Planet"))
	{
		m_respawnPlanet();
		m_moveAlongPath = false;
	}

	ImGui::SameLine();

	if (ImGui::Button("Respawn Mines"))
	{
		m_respawnMines();
		m_moveAlongPath = false;
	}

	ImGui::SameLine();

	if (ImGui::Button("Toggle Grid"))
	{
		m_debugMode = (m_debugMode) ? false : true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset All"))
	{
		m_resetAll();
	}

	ImGui::PushItemWidth(80);
	if (ImGui::SliderFloat("Manhattan Factor", m_grid[0][0]->getManhanttanFactor(), 0.1f, 10.0f, "%.1f"))
	{
		float newFactor = *m_grid[0][0]->getManhanttanFactor();

		for (size_t row = 0; row < m_rowSize; row++)
		{
			for (size_t col = 0; col < m_colSize; col++)
			{
				m_grid[col][row]->setManhanttanFactor(newFactor);
			}
		}
	}

	ImGui::SameLine();

	if (ImGui::SliderFloat("Euclidean Factor", m_grid[0][0]->getEuclideanFactor(), 0.1f, 10.0f, "%.1f"))
	{
		float newFactor = *m_grid[0][0]->getEuclideanFactor();

		for (size_t row = 0; row < m_rowSize; row++)
		{
			for (size_t col = 0; col < m_colSize; col++)
			{
				m_grid[col][row]->setEuclideanFactor(newFactor);
			}
		}
	}

	ImGui::SameLine();

	if (ImGui::SliderFloat("Mine Factor", m_grid[0][0]->getMineFactor(), 0.1f, 10.0f, "%.1f"))
	{
		float newFactor = *m_grid[0][0]->getMineFactor();

		for (size_t row = 0; row < m_rowSize; row++)
		{
			for (size_t col = 0; col < m_colSize; col++)
			{
				m_grid[col][row]->setMineFactor(newFactor);
			}
		}
	}
	ImGui::PopItemWidth();

	if (ImGui::CollapsingHeader("Ship Locations"))
	{
		ImGui::PushItemWidth(80);
		int count = 0;

		std::string shipText;
		shipText = "Ship " + count;
		shipText += " Position: ";
		ImGui::Text(shipText.c_str());
		ImGui::SameLine();
		glm::vec2 pos = m_ship.getPosition();
		ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
		count++;
		ImGui::PopItemWidth();
	}

	if (ImGui::CollapsingHeader("Planet Location"))
	{
		ImGui::PushItemWidth(80);
		std::string planetText;
		planetText = "Planet Position: ";
		ImGui::Text(planetText.c_str());
		ImGui::SameLine();
		glm::vec2 pos = m_planet.getPosition();
		ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
		ImGui::PopItemWidth();
	}

	if (ImGui::CollapsingHeader("Mine Locations"))
	{
		ImGui::PushItemWidth(80);
		int count = 0;
		for (Mine mine : m_pMines)
		{
			std::string mineText;
			mineText = "Mine " + count;
			mineText += " Position: ";
			ImGui::Text(mineText.c_str());
			ImGui::SameLine();
			glm::vec2 pos = mine.getPosition();
			ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
			count++;
		}
		ImGui::PopItemWidth();
	}

	ImGui::Separator();

	ImGui::PushItemWidth(80);
	glm::vec2 targetPosition = getTargetPosition();
	if (ImGui::SliderFloat("Target X Position", &targetPosition.x, 0.0f, 800.0f, "%.0f"))
	{
		setTargetPosition(targetPosition);
	}
	ImGui::SameLine();
	if (ImGui::SliderFloat("Target Y Position", &targetPosition.y, 0.0f, 600.0f, "%.0f"))
	{
		setTargetPosition(targetPosition);
	}
	ImGui::PopItemWidth();

	ImGui::Separator();

	if (ImGui::Button("Find Path"))
	{
		//std::cout << "**** NEW PATH ****" << std::endl;

		findShortestPath();
		m_moveAlongPath = false;
	}

	if (ImGui::CollapsingHeader("Open Tiles"))
	{
		ImGui::PushItemWidth(80);
		int count = 0;
		for (Tile* tile : m_pOpen)
		{
			std::string tileText;
			tileText = "Tile ";
			tileText += std::to_string(count);
			tileText += " Position: ";
			ImGui::Text(tileText.c_str());
			ImGui::SameLine();
			glm::vec2 pos = tile->getPosition();
			ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
			count++;
		}
		ImGui::PopItemWidth();
	}

	if (ImGui::CollapsingHeader("Closed Tiles"))
	{
		ImGui::PushItemWidth(80);
		int count = 0;
		for (Tile* tile : m_pClosed)
		{
			std::string tileText;
			tileText = "Tile ";
			tileText += std::to_string(count);
			tileText += " Position: ";
			ImGui::Text(tileText.c_str());
			ImGui::SameLine();
			glm::vec2 pos = tile->getPosition();
			ImGui::InputFloat2("", &pos[0], 0, ImGuiInputTextFlags_ReadOnly);
			count++;
		}
		ImGui::PopItemWidth();
	}

	if (!m_pOpen.empty())
	{
		if (ImGui::Button("Move Ship Along Path"))
		{
			m_moveAlongPath = true;
			m_pathLength = 0;
		}
	}

	// Main Window End
	ImGui::End();
}

/*** SCENE FUNCTIONS ***/
void PlayScene::m_resetAll()
{
	m_respawnMines();
	m_respawnPlanet();
	m_respawnShips();
}

void PlayScene::start()
{
	m_createGrid();
	m_createMines();
	m_createPlanet();
	m_pTarget = Target();
	m_createShips();
	m_pTarget.setPosition(m_ship.getPosition());

	SDL_Color blue = { 0, 0, 255, 255 };
	m_pLabel = new Label("Pathfinding Simulator", "Dock51", 40, blue, glm::vec2(400.0f, 40.0f));
}

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
{
}

void PlayScene::draw()
{
	if (m_debugMode) 
	{
		m_drawGrid();
		m_pTarget.draw();
	}
	
	m_drawShips();
	m_drawMines();

	m_planet.draw();

	//m_pLabel->draw();

	// ImGui Rendering section - DO NOT MOVE OR DELETE
	if (m_displayUI)
	{
		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 255);
	}
}

void PlayScene::update()
{
	m_updateGrid();

	m_updateShips();
	m_updateMines();

	m_pTarget.update();

	m_planet.update();

	if (m_displayUI)
	{
		m_updateUI();
	}

	if (m_moveAlongPath)
	{
		m_moveShipsAlongPath();
	}
}

void PlayScene::clean()
{
	//std::cout << "playscene clean called" << std::endl;
	delete m_pLabel;

	m_pOpen.clear();
	m_pOpen.resize(0);
	m_pOpen.shrink_to_fit();

	m_pClosed.clear();
	m_pClosed.resize(0);
	m_pClosed.shrink_to_fit();

	removeAllChildren();
}

void PlayScene::handleEvents()
{
	ImGuiIO& io = ImGui::GetIO();
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
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_TEXTINPUT:
			io.AddInputCharactersUTF8(event.text.text);
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
			case SDLK_BACKQUOTE:
				m_displayUI = (m_displayUI) ? false : true;
				break;
			case SDLK_f:
				//std::cout << "**** NEW PATH ****" << std::endl;

				findShortestPath();
				m_moveAlongPath = false;
				break;
			case SDLK_g:
				m_debugMode = (m_debugMode) ? false : true;
				break;
			case SDLK_m:
				m_moveAlongPath = true;
				m_pathLength = 0;
				break;
			case SDLK_p:
				m_respawnPlanet();
				break;
			case SDLK_r:
				m_resetAll();
				break;

				/************************************************************************/
			case SDLK_w:
				m_pTarget.setVelocity(glm::vec2(m_pTarget.getVelocity().x, -1.0f));
				break;
			case SDLK_s:
				m_pTarget.setVelocity(glm::vec2(m_pTarget.getVelocity().x, 1.0f));
				break;
			case SDLK_a:
				m_pTarget.setVelocity(glm::vec2(-1.0f, m_pTarget.getVelocity().y));
				break;
			case SDLK_d:
				m_pTarget.setVelocity(glm::vec2(1.0f, m_pTarget.getVelocity().y));
				break;
			}
			{
				int key = event.key.keysym.scancode;
				IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
				io.KeysDown[key] = (event.type == SDL_KEYDOWN);
				io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
				io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
				io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
				io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				if (m_pTarget.getVelocity().y < 0.0f) {
					m_pTarget.setVelocity(glm::vec2(m_pTarget.getVelocity().x, 0.0f));
				}
				break;

			case SDLK_s:
				if (m_pTarget.getVelocity().y > 0.0f) {
					m_pTarget.setVelocity(glm::vec2(m_pTarget.getVelocity().x, 0.0f));
				}
				break;

			case SDLK_a:
				if (m_pTarget.getVelocity().x < 0.0f) {
					m_pTarget.setVelocity(glm::vec2(0.0f, m_pTarget.getVelocity().y));
				}
				break;
			case SDLK_d:
				if (m_pTarget.getVelocity().x > 0.0f) {
					m_pTarget.setVelocity(glm::vec2(0.0f, m_pTarget.getVelocity().y));
				}
				break;
			}
			{
				int key = event.key.keysym.scancode;
				IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
				io.KeysDown[key] = (event.type == SDL_KEYDOWN);
				io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
				io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
				io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
				io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			}
			break;
		default:
			break;
		}
	}

	io.DeltaTime = 1.0f / 60.0f;
	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
	io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	io.MouseWheel = static_cast<float>(wheel);

	io.DisplaySize.x = 1280;
	io.DisplaySize.y = 720;

	m_ImGuiKeyMap();
	m_ImGuiSetStyle();
}
