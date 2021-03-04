#pragma once

#include "SOOGL/Graphics/color.hpp"
#include "Game/Updatable.hpp"

namespace gd
{
	using namespace sgl::color;

	class Color : public Updatable
	{
	public:
		color4f out_color;
		color4f begin_color;
		color4f end_color;
		double change_time = 0.0;
		double time_passed = 0.0;
	public:
		const color4f& color() const;

		void change(const color4f& new_col, double time = 0.0);
		void pulse(const color4f& new_col, double time);
		void update(double delta) override;
	};
}