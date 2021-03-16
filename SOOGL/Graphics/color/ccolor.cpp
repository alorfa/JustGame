#pragma once

#include "../color.hpp"

namespace sgl
{
	color3b::color3b(const color3f&& col)
	{
		r = ubyte(col.r * 255.f);
		g = ubyte(col.g * 255.f);
		b = ubyte(col.b * 255.f);
	}
	color4f::color4f(const color3f&& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = 1.f;
	}
	color4b::color4b(const color3b&& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = 255;
	}
}