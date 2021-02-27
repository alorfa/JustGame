#include "Clock.hpp"
#include <ctime>
//using namespace std::chrono;

namespace sgl
{
	double Clock::update()
	{
		//auto new_time = high_resolution_clock::now();
		uint new_time = std::clock();

		auto output = new_time - time;

		time = new_time;

		//return double(output.count()) / 1'000'000'000.0;
		return double(output) / 1000.0;
	}
}