#pragma once
#ifndef __FontManager__
#define __FontManager__

// Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

#include <glm\vec2.hpp>

// SDL Libraries
#include<SDL.h>
#include<SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "TextureManager.h"

class FontManager 
{
public:
	static FontManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new FontManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, int size, int style = TTF_STYLE_NORMAL);
	bool textToTexture(std::string text, std::string fontID, std::string textureID, SDL_Color colour = { 0, 0, 0, 255 });
	TTF_Font* getFont(std::string id);
	void clean();

private:
	FontManager();
	~FontManager();

	std::unordered_map<std::string, TTF_Font*> m_fontMap;

	static FontManager* s_pInstance;

};


#endif /* defined(__FontManager__) */
