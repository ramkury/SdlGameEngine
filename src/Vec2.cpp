#include "Vec2.h"
#include "Utils.h"
#include <cmath>


Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2 Vec2::operator+(const Vec2 & rhs)
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 & rhs)
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar)
{
	return Vec2(x * scalar, y * scalar);
}

float Vec2::Abs()
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::Norm()
{
	float abs = Abs();
	return Vec2(x / abs, y / abs);
}

float Vec2::Distance(Vec2 & other)
{
	return (*this - other).Abs();
}

float Vec2::Angle()
{
	return Utils::Rad2Deg(atan2f(y, x));
}

Vec2 Vec2::Rotate(float degrees)
{
	float rad = Utils::Deg2Rad(degrees);
	float cos_rad = cosf(rad);
	float sin_rad = sinf(rad);
	Vec2 result;
	result.x = x * cos_rad - y * sin_rad;
	result.y = y * cos_rad + x * sin_rad;
	return result;
}


