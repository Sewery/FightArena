
#include "LightEntity.h"

LightEntity::LightEntity(const std::string& textureFile, SDL_Renderer* ren, SDL_Rect texture,SDL_FRect collisionBox,bool isSolid,bool isLadder) : eRenderer(ren), isLadder(isLadder), isSolid(isSolid) {
	eTextures = new LightTexture(textureFile, texture, ren);
	eCollisionBox = new CollisionBox(collisionBox, collisionBox, texture.w, texture.h);
}
LightEntity::~LightEntity()
{
	eTextures->free();
}
