#include "Player.h"
#include "../Core/Window.h"

Player::Player( const std::string& textureFile, SDL_Renderer* ren, SDL_Rect pos, SDL_FRect box) :LightEntity(textureFile,ren, pos,box,true,false) {
	notScaledWinPlayerPosition = {
		(float)pos.x,
		(float)pos.y,
		(float)pos.w,
		(float)pos.h 
	};
}
Player::~Player()
{
	close();
}
bool Player::loadMedia()
{
	bool success = true;

	if (!eTextures->loadFileWithTranColor(179, 176, 187))
	{
		std::cerr << "Failed to load walking animation texture of player!\n";
		return success = false;
	}
	positionOfImages();
	return true;
}
void  Player::update(std::vector<LightEntity*>& vecBox)
{
	
	std::pair<float, float>  change = { 0.f,0.f };
	bool isStand = true;
	//Checks if player falls due to gravity
	checkFalling(change, this->eCollisionBox, vecBox, isStand);

	if ( !currentMovement[FALL] && (MouseKeyContr::mouseClick || ( currentMovement[ATTACK] && currentFrame != 0)) ) { //Checks if it is possible to attack
		isStand = false;
		attack(change, this->eCollisionBox, vecBox);
	}
	else //we can't attack and move
	{
		if (MouseKeyContr::keyboardState[SDLK_w] && !currentMovement[FALL] && eCollisionBox->isOnTheLadder(vecBox) ) {
			isStand = false;
			moveUp(change, this->eCollisionBox, vecBox);
		}
		else if (MouseKeyContr::keyboardState[SDLK_s] && !currentMovement[FALL] && eCollisionBox->isOnTheLadder(vecBox)){
			isStand = false;
			moveDown(change, this->eCollisionBox, vecBox);
		}
		else{
			
			if (!(MouseKeyContr::keyboardState[SDLK_a] && MouseKeyContr::keyboardState[SDLK_d]))//don't want left and right simounteneously
			{
				if (MouseKeyContr::keyboardState[SDLK_a]) {
					isStand = false;
					moveLeft(change, this->eCollisionBox, vecBox);
				}
				if (MouseKeyContr::keyboardState[SDLK_d]) {
					isStand = false;
					moveRight(change, this->eCollisionBox, vecBox);
				}
			}
		
			if ( (MouseKeyContr::keyboardState[SDLK_SPACE] || ((currentMovement[JUMP] && (currentFrame != (positionOfMovement[currSide][JUMP].size()) * delayRender.at(JUMP) - 1)))) && !currentMovement[FALL]) {
				isStand = false;
				jump(change, this->eCollisionBox, vecBox, 0);
			}
		}
	}
	if (isStand && !currentMovement[FALL]) {
		idle(change, this->eCollisionBox, vecBox);
	}
	notScaledWinPlayerPosition = {
		notScaledWinPlayerPosition.x + change.first,
		notScaledWinPlayerPosition.y + change.second,
		notScaledWinPlayerPosition.w,
		notScaledWinPlayerPosition.h
	};
}
void Player::render(float ratioW, float ratioH)
{
	//std::cout << "side"<<side;
	if(currentAnimation==FALL)
		eTextures->render( positionOfMovement[currSide][currentAnimation][0], resizeRect(ratioW, ratioH, this->notScaledWinPlayerPosition));
	else
		eTextures->render( positionOfMovement[currSide][currentAnimation][currentFrame/ delayRender.at(currentAnimation)], resizeRect(ratioW, ratioH, this->notScaledWinPlayerPosition));

}
void Player::render(float ratioW, float ratioH,SDL_FRect rect)
{
	eTextures->render( positionOfMovement[currSide][currentAnimation][0 / delayRender.at(currentAnimation)], resizeRect(ratioW, ratioH, this->notScaledWinPlayerPosition)) ;

}
void Player::close()
{
	eTextures->free();
}