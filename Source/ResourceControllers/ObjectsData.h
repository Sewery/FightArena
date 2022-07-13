#pragma once
#include "../Util/Config.hpp"
namespace ObjectsData
{
	//Tiles
	const  std::string imageTilesPath = "Resource/Pictures/Tiles.xcf";
	const SDL_Rect positonTiles = {0, 0, 128, 94};
	const SDL_FRect positonFTiles = { 0.0,0.0,128.0,94.0 };
	//Player
	const  std::string imagePlayerPath = "Resource/Pictures/Cyborg.xcf";
	const SDL_Rect positonPlayer1 = { 0,0,48,48 };
	const SDL_FRect boxPlayer1 = { 7,14,14,34 }; //7 14 14 34

	//Font
	const std::string fontPath = "Resource/Fonts/AnekLatin.ttf";
	const SDL_Rect positonFont = { 0,0,60,60 };
	const SDL_FRect boxFont = { 0,0,50,50 };

	//Background
	const std::string backgroundPath = "Resource/Pictures/Background.png";
	const SDL_Rect positionBackground = { 0, 0, 324, 576 };
	const SDL_FRect positionFBackground = { 0.f, 0.f, 324.f, 576.f };

	//Music
	const std::string musicPath = "Resource/Music/test.wav";
	//Objects
	enum  class WorldObject {
		LADDER,
		BENCH,
		TREE
	};
	const  std::string extension= ".png";
	//Main Folder
	static const  std::string folderObj = "Resource/Pictures/Objects";
	//Subfolders
	const  std::string	folderBushes = "Bushes";
	const  std::string  OfolderFence = "Fence";
	const  std::string  folderFountain = "Fountain";
	const  std::string  folderGrass = "Grass";
	const  std::string  folderLeaf = "Leaf";
	const  std::string  folderOther = "Other";
	const  std::string  folderStones = "Stones";


	const  int ladderWidth = 23;
	const  int ladderHeight = 32;
	//Some paths
	const static std::unordered_map< WorldObject, const std::string> objPaths;
};

