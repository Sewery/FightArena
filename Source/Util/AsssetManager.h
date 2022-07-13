#pragma once
#include "../ResourceControllers/BlockData.h"
#include "../ResourceControllers/ObjectsData.h"

struct AssetManager
{

	static std::string getPathOfBlockMapEntity(int number) {
		std::string num = std::to_string(number);
		if (number < 10) {
			num = "0" + num;
		}
		return BlockData::path + num + BlockData::extension;
	}
	static std::string getPathOfObjectEntity(ObjectsData::WorldObject obj,int number) {
		
		std::string num = std::to_string(number);
		return ObjectsData::folderObj
			+ "/" + ObjectsData::folderOther
			+ "/" +"Ladder"+num+ObjectsData::extension;
	}
};