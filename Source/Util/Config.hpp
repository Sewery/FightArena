#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <unordered_map>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#define ZERO_FRECT SDL_FRect({0.f,0.f,0.f,0.f})

static SDL_FRect resizeRect(float w,float h, SDL_FRect rect)
{
	rect.x = rect.x * w;
	rect.y = rect.y * h;
	rect.w = rect.w * w;
	rect.h = rect.h * h;
	return rect;
}

//template< class T > 
//using pair = pair< T, T >;

template<typename T>
using SPtr = std::shared_ptr<T>;

template<typename T>
using WPtr = std::weak_ptr<T>;

template<typename T>
using Uptr = std::unique_ptr<T>;

