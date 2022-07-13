#pragma once
#include "../Util/Config.hpp"

class LightTexture
{
private:
	const std::string path;
	SDL_FRect windowPositionSize;
	SDL_Rect srcPositionSize;
	SDL_Texture* tTexture;
	//The window renderer
	SDL_Renderer* tRenderer;
public:
	LightTexture(const std::string &, SDL_Rect, SDL_Renderer*);
	~LightTexture();
	void free();
	bool loadFile();
	//Creates image from font string
	bool loadFileWithTranColor(int , int , int );
	bool loadFromRenderedText(const std::string &, SDL_Color, TTF_Font*);
	void render(SDL_Rect, SDL_FRect);
	void render(SDL_Rect, SDL_FRect, SDL_RendererFlip , float =0.0, SDL_FPoint* =nullptr ) ;
	void setPositionSizeWin(SDL_FRect);
	void setPositionSizeSrc(SDL_Rect);
	void setRenderer(SDL_Renderer*);
	float getHeight() const;
	float getWidth() const;
	float getPosX() const;
	float getPosY() const;
	SDL_FRect getPositionSizeWin() ;
	SDL_Rect getPositionSizeSrc();

};