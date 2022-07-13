#include "MouseKeyContr.h"

std::unordered_map<SDL_KeyCode, bool> MouseKeyContr::keyboardState = {
	{SDLK_a, false},
	{SDLK_d,false},
	{SDLK_w,false},
	{SDLK_s,false},
	{SDLK_SPACE,false},
	{SDLK_0,false},
	{SDLK_1,false},
	{SDLK_2,false},
	{SDLK_3,false}
	
};
bool MouseKeyContr::mouseClick = false;
