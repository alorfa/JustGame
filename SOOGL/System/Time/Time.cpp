#include "Time.hpp"

#include <thread>
#include <chrono>

using std::this_thread::sleep_for;

namespace sgl
{
	void Time::wait(ulong milliseconds)
	{
		using namespace std;

		sleep_for(chrono::milliseconds(milliseconds));
	}
	void Time::wait(double sec)
	{
		wait(ulong(sec * 1000.0));
	}
}