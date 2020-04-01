#pragma once
#ifndef __TextureManager__
#define __TextureManager__

// Core Libraries
#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/vec2.hpp"

// SDL Libraries
#include<SDL.h>

#include "Config.h"
#include "SpriteSheet.h"
#include "Animation.h"

class TextureManager {
public:
	static TextureManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}
	

	bool load(const std::string& file_name, const std::string& id, SDL_Renderer* renderer);

	bool loadSpriteSheet(const std::string& data_file_name, const std::string& texture_file_name, const std::string& sprite_sheet_name, SDL_Renderer* renderer);
	

	void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(const std::string& id, int x, int y, SDL_Renderer* renderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* renderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void draw(const std::string& id, int x, int y, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(const std::string& id, int x, int y, int width, int height, int current_row, int current_frame, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int current_row, int current_frame, SDL_Renderer* renderer, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int width, int height, int current_row, int current_frame, SDL_Renderer* renderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string& id, int x, int y, int current_row, int current_frame, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(const std::string& id, int x, int y, int frame_width, int frame_height, 
		int &current_row, int &current_frame, int frame_number, int row_number, float speed_factor, 
		SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void animateFrames(int frame_width, int frame_height, int frame_number, int row_number, float speed_factor, int &current_frame, int &current_row);

	void playAnimation(const std::string& sprite_sheet_name, Animation& animation, int x, int y, int& current_frame, float speed_factor, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	void drawText(const std::string& id, int x, int y, SDL_Renderer* renderer, double angle, int alpha, bool centered = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

	glm::vec2 getTextureSize(const std::string& id);

	void setAlpha(const std::string& id, Uint8 new_alpha);

	void setColour(const std::string& id, Uint8 red, Uint8 green, Uint8 blue);

	bool addTexture(const std::string& id, std::shared_ptr<SDL_Texture> texture);
	SDL_Texture* getTexture(const std::string& id);

	void removeTexture(const std::string& id);
	int getTextureMapSize() const;

	void clean();

	void displayTextureMap();

	SpriteSheet* getSpriteSheet(const std::string& name);

private:

	TextureManager();
	~TextureManager();

	bool m_textureExists(const std::string& id);
	bool m_spriteSheetExists(const std::string& sprite_sheet_name);
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_textureMap;
	std::unordered_map<std::string, SpriteSheet*> m_spriteSheetMap;
	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */