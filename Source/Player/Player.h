#pragma once
#include "../Entities/LightEntity.h"
#include "PlayerMovement.h"

class Player :public LightEntity, public PlayerMovement {
private:
	//Sounds from player
	//std::vector<Mix_Music*> pMusic;
	SDL_FRect notScaledWinPlayerPosition;
public:
	Player(const std::string& , SDL_Renderer*,SDL_Rect, SDL_FRect);
	~Player();
	bool loadMedia() override;
	void update(std::vector<LightEntity*>&) ;
	void render(float, float) override;
	void render(float, float,SDL_FRect) override;
	void close() override;
};
