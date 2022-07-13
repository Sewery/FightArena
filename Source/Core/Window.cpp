#include "Window.h"
#include "Game.h"
#include "../Util/AsssetManager.h"
#include "../ResourceControllers/ObjectsData.h"
int Window::currWindowHeight = Game::SCREEN_HEIGHT;
int Window::currWindowWidth = Game::SCREEN_WIDTH ;
float  Window::ratioToBaseWidth = 1.0;
float  Window::ratioToBaseHeight= 1.0;
Window::Window(const std::string& name ) :title(name)
{
	tWindow = nullptr;
	tRenderer = nullptr;
	tMusic = nullptr;
	tFont = nullptr;
	if (!initWindow())
	{
		std::cout << "Window is not initializated\n";
		return;
	}
	std::cout << "Window is initializated\n";

	//Initialization of objects and textures
	this->initObjects();

	//Loading objects and textures
	this->loadFiles();
	
}
bool Window::initWindow()
{
	bool success = true;
	tWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, currWindowWidth, currWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	resizeFromBase(this->ratioToBaseWidth,this->ratioToBaseHeight);
	if (tWindow == nullptr)
	{
		std::cerr<<"Window could not be created! SDL Error: "<< SDL_GetError()<<"\n";
		return success = false;
	}
	//Create vsynced renderer for window
	tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (tRenderer == nullptr)
	{
		std::cerr << "Renderer could not be created! SDL Error:"<< SDL_GetError() <<"\n";
		return success = false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(tRenderer, 38, 210, 0xFF, 0xFF);
	return success;
}
void Window::initObjects()
{
	//Initialization of objects and textures
	background = new LightTexture(ObjectsData::backgroundPath, ObjectsData::positionBackground, tRenderer);
	player = new Player(ObjectsData::imagePlayerPath, tRenderer, ObjectsData::positonPlayer1, ObjectsData::boxPlayer1);
	tFontTexture = new LightTexture(ObjectsData::fontPath, ObjectsData::positonFont, tRenderer);
	tEntityBlocks.push_back(new ConstantBlock(ObjectsData::imageTilesPath, tRenderer,  ObjectsData::positonTiles, ObjectsData::positonFTiles,true,false));

	
	//unordered_map
	for (int i = 0; i < BlockData::winBlockSizeHeight; i++){
		for (int j = 0; j < BlockData::winBlockSizeWidth; j++){
			if (BlockData::unordered_mapOfTheBlocks[i][j] != 0){
				SDL_Rect pos = {
					0,
					0,
					BlockData::blockWidth,
					BlockData::blockHeight
				};
				SDL_FRect posf = {
					0.f,
					0.f,
					(float)BlockData::blockWidth,
					(float)BlockData::blockHeight
				};
				tEntityBlocks.push_back(new ConstantBlock(AssetManager::getPathOfBlockMapEntity(BlockData::unordered_mapOfTheBlocks[i][j]), tRenderer, pos, posf,true,false));
			}
		}
	}
	//ladders
	for (int i = 4; i < 17; i++) {
		tEntityBlocks.push_back(new ConstantBlock(AssetManager::getPathOfObjectEntity(ObjectsData::WorldObject::LADDER, 1)
			, tRenderer
			, { 0,0,ObjectsData::ladderWidth,ObjectsData::ladderHeight }
		, { 0.f,0.f,(float)ObjectsData::ladderWidth,(float)ObjectsData::ladderHeight }, false, true));
	}
}
bool Window::loadFiles()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	success = player->loadMedia();
	for (auto p : tEntityBlocks){
		success = p->loadMedia();
	}
	background->loadFile();
	//Load music
	tMusic = Mix_LoadMUS(ObjectsData::musicPath.c_str());
	if (tMusic == nullptr)
	{
		std::cerr<<"Mix_LoadMUS:"<< Mix_GetError()<< "\n";
		return 	success = false;
	}
	Mix_PlayMusic(tMusic, -1);

	//Open the font
	tFont = TTF_OpenFont(ObjectsData::fontPath.c_str(), 28);
	if (tFont == nullptr)
	{
		std::cerr << "Failed to load lazy font! SDL_ttf Error:" << TTF_GetError()<<"\n" ;
		return success = false;
	}

	//Load text
	SDL_Color textColor = { 0, 0, 0 };
	if (!tFontTexture->loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, tFont))
	{
		std::cerr << "Failed to render text texture!\n";
		return success = false;
	}
	
	return success;
}
void Window::update()
{
	//Clear screen
	resizeFromBase(this->ratioToBaseWidth, this->ratioToBaseHeight);
	SDL_SetRenderDrawColor(tRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(tRenderer);
	//Background
	background->render(ObjectsData::positionBackground, { 
		0.f,
		0.f,
		(float)currWindowWidth, 
		(float)currWindowHeight 
		});
	
	//Update and render objects
	tEntityBlocks[0]->render(ratioToBaseWidth, ratioToBaseHeight, {
			200.f,
			200.f ,
			128.0f ,
			96.0f
		});
	int k = 1;
	for (int i = 0; i < BlockData::winBlockSizeHeight; i++) {
		for (int j = 0; j < BlockData::winBlockSizeWidth; j++) {
			if (BlockData::unordered_mapOfTheBlocks[i][j] != 0) {
				tEntityBlocks[k]->render(ratioToBaseWidth, ratioToBaseHeight,{
					(float)j* BlockData::blockWidth,
					(float)i* BlockData::blockHeight,
					(float) BlockData::blockWidth ,
					(float) BlockData::blockHeight
					});
				k++;
			}
		}
	}
	//Ladders
	for (int i = 0; i < 13; i++) {
	tEntityBlocks[tEntityBlocks.size()-i-1]->render(ratioToBaseWidth, ratioToBaseHeight
		, { 7 * 32.f,(i+5) * 32.f,(float)ObjectsData::ladderWidth,(float)ObjectsData::ladderHeight });
	}
	//Update and render player
	player->update(tEntityBlocks);
	player->render(ratioToBaseWidth, ratioToBaseHeight);

	//Update the screen
	SDL_RenderPresent(tRenderer);
	
}
void Window::resizeFromBase(float ratioW, float ratioH)
{
	this->ratioToBaseWidth = ratioW;
	this->ratioToBaseHeight = ratioH;
	currWindowHeight= (int) ceil(ratioH * (float)Game::SCREEN_HEIGHT);
	currWindowWidth = (int)ceil(ratioW * (float)Game::SCREEN_WIDTH);
	SDL_SetWindowSize(tWindow, currWindowWidth, currWindowHeight);
}
void Window::close()
{
	//Free from objects
	tFontTexture->free();
	player->close();
	for (auto p : tEntityBlocks) {
		p->close();
	}

	//Free from font
	TTF_CloseFont(tFont);
	tFont = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(tRenderer);
	SDL_DestroyWindow(tWindow);
	tWindow = nullptr;
	tRenderer = nullptr;

	//Free the music
	Mix_FreeMusic(tMusic);
	tMusic = nullptr;
	
}
 
