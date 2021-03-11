#pragma once

#include "SOOGL/Graphics/Transform/Transformable2D.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	class Camera2D : public Transformable2D
	{
	public:
		Camera2D() = default;
		~Camera2D() = default;

		const mat3& matrix() const override;

		static const Camera2D by_default;
	};

	namespace transformable
	{
		using sgl::Camera2D;
	}
}