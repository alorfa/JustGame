#pragma once

#include "SOOGL/Math/vec3.hpp"

namespace sgl
{
	struct Transform3D
	{
		fvec3 position;
		vec3<float> rotation;
		fvec3 scale;
	};
}