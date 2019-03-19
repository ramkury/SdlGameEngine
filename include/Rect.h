#pragma once
#include "Vec2.h"

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	float x, y, w, h;

	// Binary operators
	float operator-(const Rect& rhs) const;
	bool operator[](const Vec2& point) const;
	Rect operator+(const Vec2& vec) const;
	Rect operator-(const Vec2& vec) const;
	
	// Methods
	Vec2 Center() const;
};
