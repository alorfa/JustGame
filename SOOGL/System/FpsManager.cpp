#include "FpsManager.hpp"
#include "SOOGL/System/Time.hpp"

namespace sgl
{
	double FpsManager::begin()
	{
		drawing_time_counter.update();

		return delta_counter.update();
	}
	void FpsManager::end()
	{
		if (limit)
		{
			double frame_time = 1.0 / (double)limit;

			double drawing_time = drawing_time_counter.update();

			if (frame_time >= drawing_time)
				Time::wait(frame_time - drawing_time);
		}
	}
}