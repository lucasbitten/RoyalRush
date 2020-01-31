#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::m_textureExists(std::string id)
{
	return m_textureMap.find(id) != m_textureMap.end();
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer * pRenderer)
{
	// check to see if texture does not already exist
	if (m_textureExists(id))
	{
		return true;
	}
	
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);

	// everything went ok, add the texture to our list
	if (pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong

	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer * pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer * pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::draw(std::string id, int x, int y, SDL_Renderer * pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer * pRenderer, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.x = textureWidth * currentFrame;
	srcRect.y = textureHeight * (currentRow - 1);
	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int currentRow, int currentFrame, SDL_Renderer * pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.x = textureWidth * currentFrame;
	srcRect.y = textureHeight * currentRow;
	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawText(std::string id, int x, int y, SDL_Renderer * pRenderer, double angle, int alpha, bool centered, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;

	int textureWidth, textureHeight;

	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &textureWidth, &textureHeight);

	srcRect.w = destRect.w = textureWidth;
	srcRect.h = destRect.h = textureHeight;

	if (centered) {
		int xOffset = textureWidth * 0.5;
		int yOffset = textureHeight * 0.5;
		destRect.x = x - xOffset;
		destRect.y = y - yOffset;
	}
	else {
		destRect.x = x;
		destRect.y = y;
	}

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

glm::vec2 TextureManager::getTextureSize(std::string id)
{
	int width, height;
	SDL_QueryTexture(m_textureMap[id], NULL, NULL, &width, &height);
	glm::vec2 size;

	size.x = width;
	size.y = height;

	return size;
}

void TextureManager::setAlpha(std::string id, Uint8 newAlpha)
{
	SDL_Texture* pTexture = m_textureMap[id];
	SDL_SetTextureAlphaMod(pTexture, newAlpha);
	SDL_DestroyTexture(pTexture);
	pTexture = NULL;
}

void TextureManager::setColour(std::string id, Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_Texture* pTexture = m_textureMap[id];
	SDL_SetTextureColorMod(pTexture, red, green, blue);
	SDL_DestroyTexture(pTexture);
	pTexture = NULL;
}

void TextureManager::addTexture(std::string id, SDL_Texture * texture)
{
	m_textureMap[id] = texture;
}

SDL_Texture * TextureManager::getTexture(std::string id)
{
	return m_textureMap[id];
}

void TextureManager::removeTexture(std::string id)
{
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}

int TextureManager::getTextureMapSize()
{
	return m_textureMap.size();
}

void TextureManager::clean()
{
	std::unordered_map<std::string, SDL_Texture*>::iterator it;

	it = m_textureMap.begin();
	while (it != m_textureMap.end())
	{
		
		SDL_DestroyTexture(it->second);
		it->second = NULL;
		m_textureMap.erase(it++);
	}
	m_textureMap.clear();
	std::cout << "TextureMap Cleared,  TextureMap Size: " << m_textureMap.size() << std::endl;
}

