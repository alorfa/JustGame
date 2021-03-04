#pragma once

#include "SOOGL/Graphics/Transform/Transform2D.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "Color.hpp"

namespace gd
{
	class Object : public sgl::Transformable2D
	{
		const Color* color;
	public:
		Object() = default;
		virtual ~Object() = default;

		virtual void draw(const sgl::Camera2D& camera) = 0;
	};
}