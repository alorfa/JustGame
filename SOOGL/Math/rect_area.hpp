#pragma once

#include "vec2.hpp"

namespace sgl
{
	template <typename T>
	struct rect_area
	{
		vec2<T> first, second;
	};
}