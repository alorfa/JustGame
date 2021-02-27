#pragma once

#include "SOOGL/Graphics/color.hpp"

namespace sgl
{
	using namespace color;
	using namespace types;

	class RenderTarget
	{
	public:
		enum class ClearBuf : uint
		{
			Color = 0x1,
			Depth = 0x2
		};

		static void clear(const color3f& color);
		static void clear(const color4f& color);
		static void clear(const color3b& color);
		static void clear(const color4b& color);

		static void clearBuffer(ClearBuf);
	};
}