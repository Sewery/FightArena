#pragma once
#include "../Util/Config.hpp"

class MouseKeyContr 
{
public:
	static std::unordered_map<SDL_KeyCode, bool> keyboardState;
	static bool mouseClick;

};
