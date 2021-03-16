#pragma once

#include "SOOGL/Other/types.hpp"
#include "color3f.hpp"

namespace sgl
{
	struct color3b
	{
		ubyte r, g, b;

		inline color3b(ubyte r = 0, ubyte g = 0, ubyte b = 0)
			: r(r), g(g), b(b) {}

		color3b(const color3f&& col);

		inline operator color3f() const {
			return color3f(255.f / r, 255.f / g, 255.f / b);
		}
		inline operator fvec3() const {
			return fvec3(color3f(*this));
		}
	};
	inline color3b operator-(const color3b& c1, const color3b& c2) {
		color3b output;
		output.r = c1.r - c2.r;
		output.g = c1.g - c2.g;
		output.b = c1.b - c2.b;
		return output;
	}
	
	namespace color
	{
		using sgl::color3b;
	}
	namespace primitives
	{
		using namespace color;
	}
}