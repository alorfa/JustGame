#pragma once

#include "SOOGL/Other/types.hpp"

namespace sgl
{
	using namespace types;

	class Time
	{
	public:
		static void wait(ulong milliseconds);
		static void wait(double seconds);
	};
}