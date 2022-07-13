#include "PlayerData.h"

void PlayerData::positionOfImages()
{

	positionOfMovement.push_back(std::unordered_map<Movement, std::vector<SDL_Rect>>());
	positionOfMovement.push_back(std::unordered_map<Movement, std::vector<SDL_Rect>>());

	for (int i = 0; i < 4; i++)
	{
		positionOfMovement[RIGHT][Movement::IDLE].push_back({ characterBoxSize * i,characterBoxSize * 7,characterBoxSize ,characterBoxSize });
		positionOfMovement[LEFT][Movement::IDLE].push_back({ widthOneSideImage - (characterBoxSize * (i + 1)),characterBoxSize * 7 + heightOneSideImage,characterBoxSize ,characterBoxSize });
	}

	for (int i = 0; i < 6; i++)
	{
		positionOfMovement[RIGHT][Movement::WALK].push_back({ characterBoxSize * i,characterBoxSize * 10,characterBoxSize ,characterBoxSize });
		positionOfMovement[LEFT][Movement::WALK].push_back({ widthOneSideImage - (characterBoxSize * (i + 1)),characterBoxSize * 10 + heightOneSideImage,characterBoxSize ,characterBoxSize });
	}

	for (int i = 0; i < 6; i++)
	{
		positionOfMovement[RIGHT][Movement::CLIMB].push_back({ characterBoxSize * i,characterBoxSize * 3,characterBoxSize ,characterBoxSize });
		positionOfMovement[LEFT][Movement::CLIMB].push_back({ widthOneSideImage - (characterBoxSize * (i + 1)),characterBoxSize * 3 + heightOneSideImage,characterBoxSize ,characterBoxSize });
	}

	for (int i = 0; i < 8; i++)
	{
		positionOfMovement[RIGHT][Movement::ATTACK].push_back({ characterBoxSize * i,characterBoxSize * 2,characterBoxSize ,characterBoxSize });
		positionOfMovement[LEFT][Movement::ATTACK].push_back({ widthOneSideImage - (characterBoxSize * (i + 1)),characterBoxSize * 2 + heightOneSideImage,characterBoxSize ,characterBoxSize });
	}

	for (int i = 0; i < 7; i++)
	{
		positionOfMovement[RIGHT][Movement::JUMP].push_back({ characterBoxSize * i,characterBoxSize * 8,characterBoxSize ,characterBoxSize });
		positionOfMovement[LEFT][Movement::JUMP].push_back({ widthOneSideImage - (characterBoxSize * (i + 1)),characterBoxSize * 8 + heightOneSideImage,characterBoxSize ,characterBoxSize });
	}

	positionOfMovement[RIGHT][Movement::FALL].push_back({ characterBoxSize * 1,characterBoxSize * 4,characterBoxSize ,characterBoxSize });
	positionOfMovement[LEFT][Movement::FALL].push_back({ widthOneSideImage - (characterBoxSize * (1 + 1)),characterBoxSize * 4 + heightOneSideImage,characterBoxSize ,characterBoxSize });
}
int PlayerData::currentFrame = 0;