#include "ConstantBlock.h"

ConstantBlock::ConstantBlock(const std::string& texture_name, SDL_Renderer* ren, SDL_Rect texture, SDL_FRect collisionBox,bool isSolid,bool isLadder) :
	LightEntity(texture_name, ren, texture, collisionBox, isSolid,isLadder) {
	this->isSolid = isSolid;
	
}

bool ConstantBlock::loadMedia()
{
	bool success = true;
	if (!eTextures->loadFile())
	{
		std::cerr << "Failed to load walking animation texture of player!\n";
		return success = false;
	}
	return success=true;
}
void ConstantBlock::render(float ratioW, float ratioH )
{
	eTextures->render(eTextures->getPositionSizeSrc(), resizeRect(ratioW, ratioH,eTextures->getPositionSizeWin()));
}
void ConstantBlock::render( float ratioW, float ratioH, SDL_FRect rect)
{
	SDL_FRect r ={
		rect.x,
		rect.y,
		(float)eTextures->getPositionSizeSrc().w,
		(float)eTextures->getPositionSizeSrc().h
	};
	eTextures->render(eTextures->getPositionSizeSrc(), resizeRect(ratioW, ratioH, r));
	eCollisionBox->setCollBox(r);
}
void ConstantBlock::close()
{
	eTextures->free();
}