#pragma once

#include "Object.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"

namespace gd
{
	class TextureObject : public Object
	{
		const sgl::Texture* texture = nullptr;
		sgl::VertexBuffer2f vbuf;
		sgl::UVBuffer ubuf;
	public:
		TextureObject();
		~TextureObject();
	};
}