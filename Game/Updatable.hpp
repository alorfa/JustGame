#pragma once

namespace gd
{
	class Updatable
	{
	public:
		virtual void update(double delta) = 0;
	};
}