#pragma once
#include "../Util/Config.hpp"

class PlayerData
{
protected:
	typedef enum
	{
		LEFT = 0,
		RIGHT = 1
	}Flip;

	typedef enum
	{
		IDLE = 0,
		WALK = 1,
		ATTACK = 2 ,
		JUMP = 3,
		CLIMB = 4,
		FALL = 5
	}Movement;

	const std::unordered_map<Movement, float> velocity = {
		{WALK,5.0f},
		{CLIMB,2.0f},
		{JUMP,2.9f},
		{FALL,3.2f}
	};
	const std::unordered_map<Movement, int> delayRender = {
		{WALK,6},
		{IDLE,11},
		{CLIMB,10},
		{ATTACK,5},
		{JUMP,4}
	};
	Movement currentMovement = IDLE;
	Flip currSide = RIGHT;
	std::vector< std::unordered_map<Movement, std::vector<SDL_Rect>>> positionOfMovement;
	const float accerationFall = 1.06f;
	static const int typesOfMoving = 6;
	static const int heightOneSideImage = 576;
	static const int widthOneSideImage = 385;
	static const int characterBoxSize = 48;
	static int currentFrame;
	void positionOfImages();
};