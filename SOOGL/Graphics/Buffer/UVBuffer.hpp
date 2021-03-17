#pragma once

#include "DataBuffer.hpp"

namespace sgl
{
	class UVBuffer : public DataBuffer<fvec2, 2, GL_FLOAT>
	{
	public:
		inline static const UVBuffer& default_quad_UV()
		{
			static UVBuffer b;
			b.changeData() = {
				{0.f, 0.f},
				{0.f, 1.f},
				{1.f, 1.f},
				{1.f, 0.f}
			};
			return b;
		}
	};

	namespace buffer
	{
		using sgl::UVBuffer;
	}
}