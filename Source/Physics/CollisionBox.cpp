#include "CollisionBox.h"
#include "../Entities/LightEntity.h"

CollisionBox::CollisionBox(SDL_FRect curr,SDL_FRect zero,int w ,int h) {
	currCollBox = curr;
	zeroCollBox = zero;
	textureW = w;
	textureH = h;
}
void CollisionBox::setCollBox(SDL_FRect rect)
{
	currCollBox = rect;
}
void CollisionBox::setZeroCollBox(SDL_FRect rect)
{
	zeroCollBox = rect;
}
std::pair<float, float> CollisionBox::move(std::vector< LightEntity*>& blocks, float x, float y ,const int  screenW,const int screenH, PositionChange lastChange)
{
	//std::cout <<"Co"<< screenW << " " << screenH << '|';
	bool moveY = false, moveX = false;
	if (x != 0)
		moveX = true;
	if(y!=0)
		moveY = true;
	if (moveX && moveY)
	{
		std::cerr << "It is not allowed to make two moves at the same time\n";
		return { -1.f,-1.f };
	}
	float finalX = currCollBox.x +x , finalY = currCollBox.y + y;
	for(auto point: blocks)
	{
		if (point->isLadder ||!point->isSolid)
			continue;
		float blockX = point->eCollisionBox->getCollBox().x, blockY = point->eCollisionBox->getCollBox().y;
		float blockW = point->eCollisionBox->getCollBox().w, blockH = point->eCollisionBox->getCollBox().h;
		if (overlapTwoRect({ finalX,finalY }, { finalX + currCollBox.w,finalY + currCollBox.h }, { blockX ,blockY }, { blockX + blockW,blockY + blockH }) 
			&& lastChange!= PositionChange::ON_LADDER)
		{
			if (moveX)
			{
				if (lastChange == PositionChange::LEFT_SIDE && (currCollBox.x+ 2*(zeroCollBox.w) - textureW) <= blockX && x<0){
					finalX = std::min(finalX, blockX - currCollBox.w);
				}
				else if (lastChange ==PositionChange::RIGHT_SIDE && (currCollBox.x + textureW -2*(zeroCollBox.w)) >= (blockX + blockW) && x > 0){
					finalX = std::max(finalX, blockX + blockW);
				}
				else if (x > 0 ){
					finalX =std::min(finalX, blockX - currCollBox.w);
				}
				else if (x < 0){
					finalX= std::max(finalX, blockX+ blockW);
				}
			}
			else if (moveY){
				if (y > 0){
					finalY = std::min(finalY, blockY - currCollBox.h);
				}
				else if (y < 0){
					finalY = std::max(finalY, blockY + blockH);
				}
			}			
		}
	}
	if (finalX <0 )
		finalX = 0;
	if (finalY <0 )
		finalY = 0;
	if (finalX > screenW - currCollBox.w)
		finalX = screenW - currCollBox.w;
	if (finalY > screenH - currCollBox.h)
		finalY = screenH - currCollBox.h;
	std::pair<float, float> diff = { finalX - currCollBox.x ,finalY - currCollBox.y };
	currCollBox.x = finalX; currCollBox.y = finalY;
	return diff;
}
bool CollisionBox::isOnTheLadder(std::vector< LightEntity*>& blocks)
{
	bool isOnTheLadder = false;
	float finalX = currCollBox.x, finalY = currCollBox.y;
	for (LightEntity* point : blocks)
	{
		float blockX = point->eCollisionBox->getCollBox().x, blockY = point->eCollisionBox->getCollBox().y;
		float blockW = point->eCollisionBox->getCollBox().w, blockH = point->eCollisionBox->getCollBox().h;
		if (overlapTwoRect({ finalX,finalY }, { finalX + currCollBox.w,finalY + currCollBox.h }, { blockX ,blockY }, { blockX + blockW,blockY + blockH }) && point->isLadder){
			isOnTheLadder=true;
		}
	}
	return isOnTheLadder;
}
SDL_FRect CollisionBox::getCollBox() const
{
	return currCollBox;
}