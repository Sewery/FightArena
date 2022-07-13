#include "AABB.h"

bool AABB::overlapTwoRect(Point LU1, Point RD1, Point LU2, Point RD2)
{
	// one on upper second on down
	if (RD1.y <= LU2.y || RD2.y <= LU1.y)
		return false;
	// one on the left second on the right
	if (RD1.x <= LU2.x || RD2.x <= LU1.x)
		return false;

	return true;
}
