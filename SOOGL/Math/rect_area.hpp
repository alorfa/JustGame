#pragma once

#include "vec2.hpp"

namespace sgl
{
	template <typename T>
	struct rect_area
	{
		vec2<T> left_bottom, right_top;

		rect_area(vec2<T> left_bottom = vec2<T>(), vec2<T> right_top = vec2<T>())
			: left_bottom(left_bottom), right_top(right_top) {}
	};

	template <typename T>
	bool in_area(vec2<T> point, rect_area<T> area)
	{
		vec2<T> size(
			area.right_top.x - area.left_bottom.x,
			area.right_top.y - area.left_bottom.y);

		// relative position from left bottom point
		vec2<T> rel_pos = point - area.left_bottom;
		
		if (rel_pos.x >= 0 && rel_pos.y >= 0)
			return (rel_pos.x < size.x) && (rel_pos.y < size.y);
		return false;
	}
}