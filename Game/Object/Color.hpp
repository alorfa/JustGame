#pragma once

#include "SOOGL/Graphics/color.hpp"
#include "Game/Updatable.hpp"

namespace gd
{
	class Color : public Updatable
	{
		sgl::color4f out_color;
		sgl::color4f begin_color;
		sgl::color4f end_color;
		double time = 0.0;
	public:
		void update(double delta) override;
		const sgl::color4f& color() const;


	};
}