#pragma once

#include "SOOGL/Other/types.hpp"

namespace sgl
{
	struct color3b;

	struct color4b
	{
		ubyte r, g, b, a;

		inline color4b(ubyte r = 0xff, ubyte g = 0xff,
			ubyte b = 0xff, ubyte a = 0xff)
			: r(r), g(g), b(b), a(a) {}

		color4b(const color3b&& other);

		inline operator color4f() const {
			return color3f(255.f / r, 255.f / g, 255.f / b);
		}
		inline operator fvec4() const {
			return fvec4(color4f(*this));
		}
	};

	namespace color
	{
		using sgl::color4b;
	}
	namespace primitives
	{
		using namespace color;
	}
}