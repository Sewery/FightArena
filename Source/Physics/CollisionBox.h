#pragma once
#include "../Util/AABB.h"

class LightEntity;
class CollisionBox: public AABB
{
private:
	SDL_FRect currCollBox;
	SDL_FRect zeroCollBox;
	int textureH;
	int textureW;
public:
	enum class PositionChange
	{
		LEFT_SIDE=0,
		RIGHT_SIDE,
		NONE,
		ON_LADDER
	};
	CollisionBox(SDL_FRect = ZERO_FRECT, SDL_FRect = ZERO_FRECT, int=0, int=0);
	std::pair<float, float> move(std::vector< LightEntity*>&,float, float, const int , const int, PositionChange);
	bool isOnTheLadder(std::vector< LightEntity*>&);
	void setCollBox(SDL_FRect);
	void setZeroCollBox(SDL_FRect);
	SDL_FRect getCollBox() const;

};

