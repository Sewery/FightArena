#include "LightTexture.h"

LightTexture::LightTexture(const std::string & path, SDL_Rect srcPosition, SDL_Renderer* tRenderer ):path(path)
{
	//Initialize
	this->tRenderer = tRenderer;
	this->srcPositionSize = srcPosition;
	tTexture = nullptr;
}

LightTexture::~LightTexture()
{
	// Deallocate
	free();
}
void LightTexture::free()
{
	// Free texture if it exists
	if (tTexture != nullptr)
	{
		SDL_DestroyTexture(tTexture);
		tTexture = nullptr;
	}
}

bool LightTexture::loadFile()
{
	//Get rid of preexisting texture
	free();
	if (tRenderer == nullptr)
	{
		std::cerr << "There is no renderer for LightTexture\n";
		return 0;
	}
	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cerr<<"Unable to load image "<<path<<" !SDL_image Error : "<<IMG_GetError()<<'\n';
		return 0;
	}

	//Create texture from surface pixels
	SDL_Texture* newTexture = nullptr;
	newTexture = SDL_CreateTextureFromSurface(tRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		std::cerr << "Unable to create texture from " << path << " !SDL Error : " << SDL_GetError() << '\n';
		return 0;
	}

	//Get image size
	if (srcPositionSize.x == -1) {
		srcPositionSize.x = 0;
		srcPositionSize.y = 0;

		srcPositionSize.w = loadedSurface->w;
		srcPositionSize.h = loadedSurface->h;
	}
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	tTexture = newTexture;
	return 1;
}
void LightTexture::render( SDL_Rect srcPS,SDL_FRect windowPS)
{
	//Set rendering space and render to screen
	srcPositionSize = srcPS;
	windowPositionSize = windowPS;
	//Render to screen
	SDL_RenderCopyF(tRenderer, tTexture, &srcPositionSize, &windowPositionSize);
}
void  LightTexture::render(SDL_Rect srcPS, SDL_FRect windowPS, SDL_RendererFlip flip, float angle, SDL_FPoint* center)
{
	//Set rendering space and render to screen
	srcPositionSize = srcPS;
	windowPositionSize = windowPS;
	//Render to screen
;	SDL_RenderCopyExF(tRenderer, tTexture, &srcPositionSize, &windowPositionSize,angle, center,flip);
}

bool LightTexture::loadFromRenderedText(const std::string& textureText, SDL_Color textColor, TTF_Font * font)
{
	//Get rid of preexisting texture
	free();
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr)
	{
		std::cerr<<"Unable to render text surface! SDL_ttf Error:"<<TTF_GetError()<<'\n';
		return 0;
	}
	else
	{
		//Create texture from surface pixels
		tTexture = SDL_CreateTextureFromSurface(tRenderer, textSurface);
		if (tTexture == nullptr)
		{
			std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << '\n';
			return 0;
		}
		windowPositionSize.w = (float) textSurface->w;
		windowPositionSize.h = (float) textSurface->h;
		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	//Return success
	return tTexture != nullptr;
}
bool LightTexture::loadFileWithTranColor(int red , int green ,int blue)
{
	//Get rid of preexisting texture
	free();
	if (tRenderer == nullptr)
	{
		std::cerr << "There is no renderer for LightTexture\n";
		return 0;
	}
	//Load image
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == nullptr)
	{
		std::cerr << "Unable to load image " << path << " !SDL_image Error : " << IMG_GetError() << '\n';
		return 0;
	}

	//Create texture from surface pixels
	SDL_Texture* newTexture = nullptr;
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, red, green, blue));
	newTexture = SDL_CreateTextureFromSurface(tRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		std::cerr << "Unable to create texture from " << path << " !SDL Error : " << SDL_GetError() << '\n';
		return 0;
	}
	//Get image size
	if (srcPositionSize.x == -1) {
		srcPositionSize.x = 0;
		srcPositionSize.y = 0;

		srcPositionSize.w = loadedSurface->w;
		srcPositionSize.h = loadedSurface->h;
	}
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	tTexture = newTexture;
	return 1;
}
void LightTexture::setPositionSizeWin(SDL_FRect rect)
{
	windowPositionSize = rect;
}
void LightTexture::setPositionSizeSrc(SDL_Rect rect)
{
	srcPositionSize = rect;
}
void LightTexture::setRenderer(SDL_Renderer* renderer)
{
	this->tRenderer = renderer;
}
float LightTexture::getWidth() const
{
	return windowPositionSize.w;
}

float LightTexture::getHeight() const
{
	return windowPositionSize.h;
}

float LightTexture::getPosX() const
{
	return windowPositionSize.x;
}

float LightTexture::getPosY() const
{
	return windowPositionSize.y;
}
SDL_Rect LightTexture::getPositionSizeSrc()
{
	return srcPositionSize;
}
SDL_FRect LightTexture::getPositionSizeWin()
{
	return windowPositionSize;
}
