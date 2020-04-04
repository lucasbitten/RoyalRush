#include "ControlsImage.h"
#include "Game.h"

ControlsImage::ControlsImage(std::string imagePath, std::string imageName, GameObjectType type, glm::vec2 position, bool isCentered)
	: m_name(imageName), m_isCentered(isCentered), m_alpha(200)
{
	TheTextureManager::Instance()->load(imagePath,
		m_name, TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_name);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
	setType(type);
}

ControlsImage::~ControlsImage()
{
}

void ControlsImage::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw(m_name, xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, m_alpha, true);
}

void ControlsImage::update()
{
}

void ControlsImage::clean()
{
}
