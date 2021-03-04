#pragma once

#include <SFML/Window/Mouse.hpp>
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	using Button = sf::Mouse::Button;

	class Mouse
	{
	public:
		static bool isPressed(Button button);

		static ivec2 position();
		static ivec2 position(const ivec2& new_pos);
	};
}