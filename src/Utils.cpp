#include "Utils.h"

float Utils::Deg2Rad(float angle)
{
	return angle * (PI / 180);
}

float Utils::Rad2Deg(float angle)
{
	return angle * (180.f / PI);
}
