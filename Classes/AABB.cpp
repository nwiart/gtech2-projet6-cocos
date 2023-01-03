#include "AABB.h"



namespace lemmings
{

AABB::AABB()
	: x0(0), y0(0), x1(0), y1(0)
{

}

AABB::AABB(float x0, float y0, float x1, float y1)
	: x0(x0), y0(y0), x1(x1), y1(y1)
{

}

float AABB::collideX(const AABB& o, float dx) const
{
	if (y1 >= o.y0 && y0 <= o.y1) {
		if (dx > 0) {
			if (x1 <= o.x0 && x1 + dx >= o.x0) {
				
				dx = o.x0 - x1 - 0.001F;
			}
		}
		else if (dx < 0) {
			if (x0 >= o.x1 && x0 + dx <= o.x1) {
				dx = o.x1 - x0;
			}
		}
	}
	return dx;
}

float AABB::collideY(const AABB& o, float dy) const
{
	if (x1 >= o.x0 && x0 <= o.x1) {
		if (dy > 0) {
			if (y1 <= o.y0 && y1 + dy >= o.y0) {
				dy = o.y0 - y1;
			}
		}
		else if (dy < 0) {
			if (y0 >= o.y1 && y0 + dy <= o.y1) {
				dy = o.y1 - y0;
			}
		}
	}
	return dy;
}

}
