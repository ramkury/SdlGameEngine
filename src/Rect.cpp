#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0)
{
}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
{
}

Vec2 Rect::Center() const
{
	return Vec2(x + (w / 2.f), y + (h / 2.f));
}

float Rect::operator-(const Rect & rhs) const
{
	return (Center() - rhs.Center()).Abs();
}

bool Rect::operator[](const Vec2 & point) const
{
	return point.x >= x 
		&& point.y >= y
		&& point.x <= (x + w)
		&& point.y <= (y + h);
}

Rect Rect::operator+(const Vec2 & vec) const
{
	return Rect(x + vec.x, y + vec.y, w, h);
}

Rect Rect::operator-(const Vec2 & vec) const
{
	return Rect(x - vec.x, y - vec.y, w, h);
}
