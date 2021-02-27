#pragma once

#include "SOOGL/Math/vec3.hpp"

namespace sgl
{
	using namespace vec;
	using namespace types;

	struct Transform3D
	{
		fvec3 position;
		vec3<rotation_type> rotation;
		fvec3 scale;
	};
}