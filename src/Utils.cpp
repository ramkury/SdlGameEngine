#include "Utils.h"

float Utils::Deg2Rad(float angle)
{
	return (angle / 180.f) * PI;
}

float Utils::Rad2Deg(float angle)
{
	return angle * (180.f * PI);
}
