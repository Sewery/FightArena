#pragma once
#include "../Texture/LightTexture.h"
#include "../Physics/CollisionBox.h"

class LightEntity 
{
public:
		bool isLadder;
		bool isSolid;
		LightTexture* eTextures;
		SDL_Renderer* eRenderer;
		CollisionBox * eCollisionBox;
		//const std::string name;
		LightEntity(const std::string&, SDL_Renderer*, SDL_Rect, SDL_FRect,bool,bool);
		~LightEntity();
		virtual bool loadMedia() = 0;
		virtual void render(float,float) = 0;
		virtual void render(float,float,SDL_FRect)=0;
		virtual void close() = 0;
};
