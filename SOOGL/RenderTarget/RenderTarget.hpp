#pragma once

#include "SOOGL/Graphics/color.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	class RenderTarget
	{
	protected:
		static uvec2 default_framebuf_size;

		static void viewport(uvec2 size);
		static void viewport(uvec2 begin, uvec2 end);
	public:
		static void clear(const color3f& color);
		static void clear(const color4f& color);
		static void clear(const color3b& color);
		static void clear(const color4b& color);
	};
}