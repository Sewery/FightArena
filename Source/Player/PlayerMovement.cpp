#include "PlayerMovement.h"
#include "../Core/Window.h"
#include "../Core/Game.h"


void PlayerMovement::checkFalling(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox, bool& isStand)
{
	if ( ( currentAnimation != JUMP || 
		  ( currentAnimation == JUMP && currentFrame == (positionOfMovement[currSide][JUMP].size() * delayRender.at(JUMP) - 1)) ) 
		&& currentAnimation != CLIMB)
	{
		currentSpeed = currentSpeed * accerationFall;
		change = collBox->move(vecBox, 0, currentSpeed, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::NONE);
		if (change.second > 0) {//If there is "air" under player it won't be 0
			if (!currentMovement[FALL])
				currentSpeed = velocity.at(FALL);
			currentMovement.fill(false);
			currentMovement[FALL] = true;
			currentAnimation = FALL;
			isStand = false;
		}
		else
		{
			currentSpeed = velocity.at(FALL);
			if (currentMovement[FALL] || currentMovement[IDLE]) {
				currentMovement.fill(false);
				currentMovement[IDLE] = true;
				currentAnimation = IDLE;
				isStand = true;
			}
		}
	}
	
}
void PlayerMovement::attack(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{
		if (!currentMovement[ATTACK])
			currentFrame = -1;
		currentMovement.fill(false);
		currentMovement[ATTACK] = true;
		currentAnimation = ATTACK;
		(currentFrame += 1) %= (positionOfMovement[currSide][ATTACK].size() * delayRender.at(ATTACK));
}
void PlayerMovement::moveLeft( std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{
		if (!currentMovement[WALK] && !currentMovement[JUMP]) {
			currentFrame = -1;
		}
		if (Flip::RIGHT == currSide){
			currSide = LEFT;
			auto rect = collBox->getCollBox();
			collBox->setCollBox({ rect.x + characterBoxSize - rect.w - collBox->getCollBox().w, rect.y ,rect.w,rect.h});
		}
		std::pair<float, float> ch = collBox->move(vecBox, -velocity.at(WALK), 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::LEFT_SIDE);
		change = { ch.first + change.first, ch.second + change.second };
		
		if (currentMovement[FALL]) {
			currentMovement.fill(false);
			currentMovement[FALL] = true;
			currentAnimation = FALL;
		}
		else if (currentMovement[JUMP] && (currentFrame != (positionOfMovement[currSide][JUMP].size()) * delayRender.at(JUMP) - 1)) {
			currentMovement.fill(false);
			currentMovement[JUMP] = true;
			currentAnimation = JUMP;
		}
		else {
			currentAnimation = WALK;
			currentMovement.fill(false);
		}
		currentMovement[WALK] = true;
		if (!currentMovement[JUMP]) {
			(currentFrame += 1) %= (positionOfMovement[currSide][WALK].size() * delayRender.at(WALK));
		}
	
}
void PlayerMovement::moveRight(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{
		if (!currentMovement[WALK] && !currentMovement[JUMP]) {
			currentFrame = -1;
		}
		if (Flip::LEFT == currSide){
			currSide = RIGHT;
			auto rect = collBox->getCollBox();
			collBox->setCollBox({ rect.x - characterBoxSize + rect.w + collBox->getCollBox().w ,rect.y,rect.w,rect.h });
		}
		std::pair<float, float> ch = collBox->move(vecBox, velocity.at(WALK), 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::RIGHT_SIDE);
		change = { ch.first + change.first, ch.second + change.second };
		if (currentMovement[FALL]) {
			currentMovement.fill(false);
			currentMovement[FALL] = true;
			currentAnimation = FALL;
		}
		else if (currentMovement[JUMP] && (currentFrame != (positionOfMovement[currSide][JUMP].size()) * delayRender.at(JUMP) - 1)) {
			currentMovement.fill(false);
			currentMovement[JUMP] = true;
			currentAnimation = JUMP;
		}
		else {
			currentAnimation = WALK;
			currentMovement.fill(false);
		}
		currentMovement[WALK] = true;
		if (currentAnimation != FALL && currentAnimation != JUMP)
			currentAnimation = WALK;
		if (!currentMovement[JUMP]) {
			(currentFrame += 1) %= (positionOfMovement[currSide][WALK].size() * delayRender.at(WALK));
		}
}
void PlayerMovement::moveUp(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{
		if (!currentMovement[CLIMB])
			currentFrame = -1;
		std::pair<float, float> ch = collBox->move(vecBox, 0, -velocity.at(CLIMB), Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::ON_LADDER);
		change = { ch.first + change.first, ch.second + change.second };
		currentMovement.fill(false);
		currentMovement[CLIMB] = true;
		currentAnimation = CLIMB;
		(currentFrame += 1) %= (positionOfMovement[currSide][CLIMB].size() * delayRender.at(CLIMB));
}
void PlayerMovement::moveDown(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{
		if (!currentMovement[CLIMB])
			currentFrame = -1;
		std::pair<float, float> ch = collBox->move(vecBox, 0, velocity.at(CLIMB), Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::ON_LADDER);
		change = { ch.first + change.first, ch.second + change.second };
		currentMovement.fill(false);
		currentMovement[CLIMB]=true;
		currentAnimation = CLIMB;
		(currentFrame += 1) %= (positionOfMovement[currSide][CLIMB].size() * delayRender.at(CLIMB));
}
void PlayerMovement::jump(std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox, const bool& inMove)
{
	if (!currentMovement[JUMP])
		currentFrame = -1;
	currentMovement.fill(false);
	if (inMove){
		currentMovement[WALK] = true;
	}
	currentMovement[JUMP] = true;
	currentAnimation = JUMP;
	std::pair<float, float> ch;
	if (currentFrame +1 >= ( ((float)positionOfMovement[currSide][Movement::JUMP].size() * (float)delayRender.at(JUMP)))/2 )
		ch = collBox->move(vecBox, 0, velocity.at(JUMP), Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::NONE);
	else
		ch = collBox->move(vecBox, 0, -velocity.at(JUMP), Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, CollisionBox::PositionChange::NONE);
	change = { 
		ch.first + change.first, 
		ch.second + change.second 
	};
	(currentFrame += 1) %= (positionOfMovement[currSide][JUMP].size() * delayRender.at(JUMP));
	
}
void PlayerMovement::idle( std::pair<float, float>& change, CollisionBox* collBox, std::vector<LightEntity*>& vecBox)
{	
	if (!currentMovement[IDLE])
		currentFrame = -1;
	currentMovement.fill(false);
	currentAnimation = IDLE;
	currentMovement[IDLE]=true;
	(currentFrame += 1) %= (positionOfMovement[currSide][IDLE].size() * delayRender.at(IDLE));
}