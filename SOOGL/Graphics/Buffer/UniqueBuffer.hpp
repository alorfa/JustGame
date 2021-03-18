#pragma once

#include "Buffer.hpp"
#include "SOOGL/Graphics/color.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	// TODO: not done
	template <typename... T>
	class UniqueBuffer
	{
		Buffer<T> buffer;
	public:
		void activate()
		{

		}
	};
}