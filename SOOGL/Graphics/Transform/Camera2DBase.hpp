#pragma once

#include "SOOGL/Math/mat3.hpp"

namespace sgl
{
	class Camera2DBase
	{
	public:
		virtual const mat3& matrix() const = 0;
	};
}