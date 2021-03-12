#pragma once

#include "FrameBuffer.hpp"

namespace sgl
{
	class RenderBuffer : public RenderTarget
	{
		FrameBuffer frame_buffer;
		uint id;
	public:
		RenderBuffer();
		~RenderBuffer();

		void create(uvec2 size);

		static bool isValid();

		void activate() const;
		static void deactivate();

		const Texture& texture() const {
			return frame_buffer.texture();
		}
	};
}