#pragma once

#include "SOOGL/Graphics/Transform/Transformable2D.hpp"
#include "SOOGL/Math/vec2.hpp"
#include "Camera2DBase.hpp"

namespace sgl
{
	class Camera2D : public Camera2DBase
	{
		mutable Transform2D top_down_transform;
	public:
		Camera2D() = default;
		~Camera2D() = default;

		// TODO: it doesn't affect anything 
		bool top_down = false;

		const Transform2D& transform() const override;

		static const Camera2D by_default;
	};

	namespace transformable
	{
		using sgl::Camera2D;
	}
}