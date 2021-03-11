#pragma once

#include <vector>
#include "Object.hpp"

namespace gd
{
	class Group
	{
		std::vector<Object*> objects;
		std::vector<fvec2*> points;
	public:
		void move(fvec2 offset);
		void rotate(float radians);
	};
}