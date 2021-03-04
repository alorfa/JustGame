#pragma once

#include "Clock.hpp"
#include "SOOGL/Other/types.hpp"

namespace sgl
{
	using namespace types;

	class FpsManager
	{
		Clock delta_counter;
		Clock drawing_time_counter;
	public:
		uint limit = 0;

		inline FpsManager() = default;

		/* Call it at the start of the main loop.
		* Returns the time delta
		*/
		double begin();

		/* Call it at the end of the main loop.
		* This method waits for the rest of the frame
		*/
		void end();
	};
}