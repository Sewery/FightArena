#pragma once
#include "Config.hpp"

class AABB
{
public:
	struct Point
	{
		float x = 0, y = 0;
	};
	bool overlapTwoRect(Point LU1, Point RD1, Point LU2, Point RD2);
};

