#include "Vec2.h"
#include "Utils.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2 Vec2::operator-() const
{
	return Vec2(-x, -y);
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

float Vec2::Abs() const
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::Norm() const
{
	float abs = Abs();
	return Vec2(x / abs, y / abs);
}

float Vec2::Distance(Vec2 & other) const
{
	return (*this - other).Abs();
}

float Vec2::Angle() const
{
	return Utils::Rad2Deg(atan2f(y, x));
}

Vec2 Vec2::Rotate(float degrees) const
{
	float rad = Utils::Deg2Rad(degrees);
	float cos_rad = cosf(rad);
	float sin_rad = sinf(rad);
	Vec2 result;
	result.x = x * cos_rad - y * sin_rad;
	result.y = y * cos_rad + x * sin_rad;
	return result;
}


