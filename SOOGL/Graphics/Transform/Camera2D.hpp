#pragma once

#include "SOOGL/Graphics/Transform/Transform2D.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	using namespace mat;
	using namespace vec;

	class Camera2D : public Transformable2D
	{
	public:
		Camera2D() = default;
		~Camera2D() = default;

		const mat3& matrix() const override;

		static const Camera2D by_default;
	};
}