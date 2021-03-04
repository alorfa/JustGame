#pragma once

#include "SOOGL/Graphics/Transform/Transform2D.hpp"

namespace gd
{
	class Player : public sgl::Transformable2D
	{
		sgl::fvec2 direction;
	public:
		virtual void draw() = 0;
	};
}