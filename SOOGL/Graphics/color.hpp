#pragma once

#include "SOOGL/Math/vec3.hpp"
#include "SOOGL/Math/vec4.hpp"

namespace sgl
{
	struct color3f
	{
		float r, g, b;

		inline color3f(float r = 0.f, float g = 0.f, float b = 0.f)
			: r(r), g(g), b(b) {}

		inline fvec3& asVec3() {
			return *(fvec3*)this;
		}
		inline const fvec3& asVec3() const {
			return *(fvec3*)this;
		}
		inline operator fvec3& () { return asVec3(); }
		inline operator const fvec3& () const { return asVec3(); }
	};

	struct color3b
	{
		types::ubyte r, g, b;

		inline color3b(types::ubyte r = 0, types::ubyte g = 0, types::ubyte b = 0)
			: r(r), g(g), b(b) {}

		inline color3f toFvec3() const {
			return color3f(255.f / r, 255.f / g, 255.f / b);
		}
	};
	inline color3b operator-(const color3b& c1, const color3b& c2) {
		color3b output;
		output.r = c1.r - c2.r;
		output.g = c1.g - c2.g;
		output.b = c1.b - c2.b;
		return output;
	}

	struct color4f
	{
		float r, g, b, a;

		inline color4f(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f)
			: r(r), g(g), b(b), a(a) {}

		inline color4f(const color3f& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = 1.f;
		}
		inline fvec4& asVec4() {
			return *(fvec4*)this;
		}
		inline const fvec4& asVec4() const {
			return *(fvec4*)this;
		}
		inline operator fvec4& () { return asVec4(); }
		inline operator const fvec4& () const { return asVec4(); }
	};

	struct color4b
	{
		sgl::types::ubyte r, g, b, a;

		inline color4b(types::ubyte r = 0xff, types::ubyte g = 0xff,
			types::ubyte b = 0xff, types::ubyte a = 0xff)
			: r(r), g(g), b(b), a(a) {}

		inline color4b(const color3b& other)
		{
			r = other.r;
			g = other.g;
			b = other.b;
			a = 255;
		}
	};

	namespace color
	{
		using sgl::color3b;
		using sgl::color4b;
		using sgl::color3f;
		using sgl::color4f;
	}
	namespace primitives
	{
		using namespace color;
	}
}