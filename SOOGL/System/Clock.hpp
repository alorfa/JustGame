#pragma once

//#include <chrono>
#include "SOOGL/Other/types.hpp"

namespace sgl
{
	//using namespace std::chrono;
	using namespace types;

	class Clock
	{
		//high_resolution_clock::time_point time;
		uint time;
	public:
		inline Clock()
		{
			update();
		}
		double update();
	};
}