#pragma once
#include "../Util/Config.hpp"
struct BlockData {
	//DataBlock
	const static int numberOfBlocks = 96;
	const static int numberOfColumns = 12;
	const static int numberOfRows = 8;
	const static int blockHeight = 32; //pixels
	const static int blockWidth = 32; //pixels

	//Data for 3:4 window to place blocks
	const static int winBlockSizeHeight = 21;
	const static int winBlockSizeWidth = 28;
	const static std::string path;
	const static std::string extension;
	const static std::vector<std::vector<int>> unordered_mapOfTheBlocks;

};
const std::string BlockData::path = "Resource/Pictures/Tiles/Tile_";
const std::string BlockData::extension = ".png";
const std::vector<std::vector<int>> BlockData::unordered_mapOfTheBlocks =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,43,2,2,2,2,2,2,2,2,34,10,10,10,33,2,2,2,2,2},
	{34,33,2,2,34,10,10,33,2,55,15,14,14,14,15,15,14,14,4,4,4,4,4,14,14,14,14,14},
	{39,4,14,14,4,40,4,4,14,15,4,4,4,4,4,39,4,4,4,4,4,4,4,4,4,37,4,4},
	{4,4,4,4,4,4,4,4,4,4,4,38,4,4,4,4,4,4,4,40,4,4,4,4,4,4,4,4}
};