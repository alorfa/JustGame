#include "Color.hpp"
#include "SOOGL/Math/vec4.hpp"

using namespace sgl::vec;

namespace gd
{
	void Color::update(double delta)
	{
		time_passed += delta;
		if (time_passed >= change_time)
		{
			out_color = begin_color = end_color;
			time_passed = change_time = 0.0;
			return;
		}
		float ratio = float(time_passed / change_time);
		auto col = (fvec4)begin_color * (1.f - ratio) + (fvec4)end_color * ratio;
		out_color = color4f(col.x, col.y, col.z, col.w);
	}
	const color4f& Color::color() const
	{
		return out_color;
	}
	void Color::change(const color4f& new_col, double time)
	{
		if (change_time > 0.0)
		{
			begin_color = out_color;
			time_passed = change_time = 0.0;
		}
		change_time = time;
		end_color = new_col;
	}
	void Color::pulse(const color4f& new_col, double time)
	{
	}
}