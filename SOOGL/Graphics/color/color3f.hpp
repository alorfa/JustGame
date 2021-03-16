#pragma once

#include "SOOGL/Math/vec3.hpp"

namespace sgl
{
	struct color3f
	{
		float r, g, b;

		inline color3f(float r = 0.f, float g = 0.f, float b = 0.f)
			: r(r), g(g), b(b) {}

		inline operator fvec3& () { return *(fvec3*)this; }
		inline operator const fvec3& () const { return *(fvec3*)this; }
	};

	namespace color
	{
		using sgl::color3f;
	}
	namespace primitives
	{
		using namespace color;
	}
}