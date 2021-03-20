#pragma once

#include "Transformable2D.hpp"

namespace sgl
{
	class Camera2DBase : public Transformable2D
	{
	public:
		virtual const Transform2D& transform() const = 0;
	};
}