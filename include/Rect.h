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
	Rect operator+(const Vec2& vec) const;
	Rect operator-(const Vec2& vec) const;
	
	// Methods
	bool Contains(const Vec2& point) const;
	Vec2 Center() const;
	void CenterAt(float cx, float cy);
	void CenterAt(Vec2 pos);
};
