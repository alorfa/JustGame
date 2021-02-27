#pragma once

#include "Object.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"

namespace gd
{
	class BitmapObject : public Object
	{
		const sgl::Texture* texture = nullptr;
	public:
		BitmapObject();
		~BitmapObject();
	};
}