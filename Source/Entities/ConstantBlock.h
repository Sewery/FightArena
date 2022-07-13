#pragma once
#include "LightEntity.h"

class ConstantBlock : public LightEntity
{
public:
	ConstantBlock(const std::string&, SDL_Renderer*, SDL_Rect , SDL_FRect,bool,bool);
	bool loadMedia();
	void render(float, float);
	void render(float, float, SDL_FRect);
	void close();

};

