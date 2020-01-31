#include "Button.h"
#include "Game.h"


Button::Button(std::string imagePath, std::string buttonName, GameObjectType type, glm::vec2 position, bool isCentered): m_name(buttonName), m_isCentered(isCentered), m_alpha(255)
{
	TheTextureManager::Instance()->load(imagePath,
		m_name, TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize(m_name);
	setWidth(size.x);
	setHeight(size.y);
	setPosition(position);
	setType(type);
}

Button::~Button()
{
}

void Button::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw(m_name, xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, m_alpha, true);
}

void Button::update()
{
}

void Button::clean()
{
}


void Button::setMousePosition(glm::vec2 mousePosition)
{
	m_mousePosition = mousePosition;
}

void Button::setMouseButtonClicked(bool clicked)
{
	m_mouseButtonClicked = clicked;
}


bool Button::m_mouseOver()
{
	const float topLeftX = getPosition().x - getWidth() * 0.5;
	const float topLeftY = getPosition().y - getHeight() * 0.5;
	const float width = getWidth();
	const float height = getHeight();

	// check if mouse is over button
	if (m_mousePosition.x > topLeftX &&
		m_mousePosition.x < topLeftX + width &&
		m_mousePosition.y > topLeftY &&
		m_mousePosition.y < topLeftY + height)
	{
		m_alpha = 178;
		return true;
	}
	else
	{
		m_alpha = 255;
		return false;
	}
}
