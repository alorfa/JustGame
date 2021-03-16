#pragma once

#include "SOOGL/Math/vec4.hpp"

namespace sgl
{
	struct color3f;

	struct color4f
	{
		float r, g, b, a;

		inline color4f(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f)
			: r(r), g(g), b(b), a(a) {}

		color4f(const color3f&& other);

		inline operator fvec4& () { return *(fvec4*)this; }
		inline operator const fvec4& () const { return *(fvec4*)this; }
	};

	namespace color
	{
		using sgl::color4f;
	}
	namespace primitives
	{
		using namespace color;
	}
}