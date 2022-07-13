#pragma once
#include "PlayerData.h"
#include "../ResourceControllers/MouseKeyContr.h"
#include "../Physics/CollisionBox.h"

class PlayerMovement :public PlayerData
{
protected:
	std::array<bool, typesOfMoving> currentMovement;
	Movement currentAnimation=IDLE;
	float currentSpeed = velocity.at(FALL);
	void checkFalling(std::pair<float, float>&, CollisionBox*, std::vector<LightEntity*>&,bool&);
	void attack(std::pair<float, float>&, CollisionBox*, std::vector<LightEntity*>&);
	void moveLeft(std::pair<float, float >&, CollisionBox*, std::vector<LightEntity*>&);
	void moveRight(std::pair<float, float>&, CollisionBox*, std::vector<LightEntity*>&);
	void moveUp(std::pair<float, float>&, CollisionBox*, std::vector<LightEntity*>&);
	void moveDown(std::pair<float, float>&, CollisionBox*, std::vector<LightEntity*>&);
	void jump(std::pair<float, float >&, CollisionBox*, std::vector<LightEntity*>&,const bool&);
	void idle(std::pair<float, float>& , CollisionBox*, std::vector<LightEntity*>&);
};
