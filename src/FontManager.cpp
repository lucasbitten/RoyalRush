#include "FontManager.h"
#include "Game.h"

FontManager* FontManager::s_pInstance = 0;


bool FontManager::load(std::string fileName, std::string id, int size, int style)
{
	TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
	if (font != 0)
	{
		TTF_SetFontStyle(font, style);
		m_fontMap[id] = font;
		return true;
	}

	return false;
}

bool FontManager::textToTexture(std::string text, std::string fontID, std::string textureID, SDL_Color colour)
{
	//Render text surface

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_fontMap[fontID] , text.c_str(), colour);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		//Create texture from surface pixels
		TextureManager::Instance()->addTexture(textureID, SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), textSurface));
		
		if (TextureManager::Instance()->getTexture(textureID) == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	TTF_CloseFont(m_fontMap[fontID]);
	m_fontMap.erase(fontID);

	return true;
}

TTF_Font * FontManager::getFont(std::string id)
{
	return m_fontMap[id];
}

void FontManager::clean()
{
	std::unordered_map<std::string, TTF_Font*>::iterator it;

	it = m_fontMap.begin();
	while (it != m_fontMap.end())
	{
		TTF_CloseFont(it->second);
		it->second = NULL;
		m_fontMap.erase(it++);
	}

	m_fontMap.clear();
}


FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}
