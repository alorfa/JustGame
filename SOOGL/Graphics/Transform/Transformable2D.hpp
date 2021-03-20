#pragma once

#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/mat3.hpp"

namespace sgl
{
	struct Transform2D
	{
		fvec2 position;
		float rotation;
		fvec2 scale;

		inline Transform2D()
			: position(), rotation(0), scale(1.f, 1.f) {};
	};

	class Transformable2D
	{
	public:
		fvec2 position;
		float rotation;
		fvec2 scale;

		inline Transformable2D() 
			: position(), rotation(0), scale(1.f, 1.f) {};
		virtual ~Transformable2D() = default;

		inline const Transform2D& transform() const {
			return *(Transform2D*)&position;
		}
	};

	namespace transformable
	{
		using sgl::Transform2D;
		using sgl::Transformable2D;
	}
}