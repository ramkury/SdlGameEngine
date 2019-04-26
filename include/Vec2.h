#pragma once
class Vec2
{
public:
	Vec2();
	Vec2(float x, float y);
	float x, y;

	// Unary operators
	Vec2 operator-() const;

	// Binary operators
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(float scalar) const;
	void operator+=(const Vec2& rhs);

	// Methods
	float Abs() const;
	Vec2 Norm() const;
	float Distance(Vec2& other) const;
	float AngleR() const;
	float AngleD() const;
	Vec2 RotateR(float radians) const;
	Vec2 RotateD(float degrees) const;
};

