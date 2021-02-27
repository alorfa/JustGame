#pragma once

#include "SOOGL/Graphics/Transform/Transform2D.hpp"

namespace gd
{
	class Player : public sgl::Transformable2D
	{
	public:
		virtual void draw() = 0;
	};
}