#include "trig.hpp"
#include <cmath>

namespace sgl
{
	constexpr float PI = 3.1415926535f;

	float deg(float radians)
	{
		return radians / PI * 180.f;
	}
	float rad(float rotation)
	{
		return rotation / 180.f * PI;
	}
}