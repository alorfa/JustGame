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
		uint id;
		Type type;
		Texture r_texture;
	public:
		FrameBuffer();
		~FrameBuffer();

		void create(uvec2 size, Image::Type pixel_format = Image::RGB, Type type = Type::Default);
		void activate() const;
		void deactivate() const;

		static bool isValid();

		inline uint nativeHandle() const {
			return id;
		}
		inline const Texture& texture() const {
			return r_texture;
		}
	};
}