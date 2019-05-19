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
	return {-x, -y};
}

Vec2 Vec2::operator+(const Vec2 & rhs) const
{
	return {x + rhs.x, y + rhs.y};
}

Vec2 Vec2::operator-(const Vec2 & rhs) const
{
	return {x - rhs.x, y - rhs.y};
}

Vec2 Vec2::operator*(float scalar) const
{
	return {x * scalar, y * scalar};
}

bool Vec2::operator==(const Vec2& rhs) const
{
	return x == rhs.x && y == rhs.y;
}

void Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

float Vec2::Abs() const
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::Norm() const
{
	const auto abs = Abs();
	return abs == 0 ? *this : Vec2(x / abs, y / abs);
}

float Vec2::DistanceTo(Vec2 & other) const
{
	return (other - *this).Abs();
}

float Vec2::AngleR() const
{
	return atan2f(y, x);
}

float Vec2::AngleD() const
{
	return Utils::Rad2Deg(AngleR());
}

Vec2 Vec2::RotateR(float radians) const
{
	const float cos_rad = cosf(radians);
	const float sin_rad = sinf(radians);
	return
	{
		x * cos_rad - y * sin_rad,
		y * cos_rad + x * sin_rad
	};
}

Vec2 Vec2::RotateD(float degrees) const
{
	return RotateR(Utils::Deg2Rad(degrees));
}

