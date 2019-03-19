#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	float x, y;

	Vec2 operator+(const Vec2& rhs);
	Vec2 operator-(const Vec2& rhs);
	Vec2 operator*(float scalar);

	float Abs();
	Vec2 Norm();
	float Distance(Vec2& other);
	float Angle();
	Vec2 Rotate(float degrees);
};

