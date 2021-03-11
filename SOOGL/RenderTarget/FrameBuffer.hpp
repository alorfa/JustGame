#pragma once

#include "RenderTarget.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"

namespace sgl
{
	class FrameBuffer : public RenderTarget
	{
	public:
		enum Type
		{
			Nothing,
			Default,
			Read,
			Draw
		};
	private:
		uint m_id;
		Type type;
		Texture texture;
	public:

		FrameBuffer();
		~FrameBuffer();

		void create(uvec2 size, Type type);

		static bool isValid();

		inline uint id() const {
			return m_id;
		}
	};
}