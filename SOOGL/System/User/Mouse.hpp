#pragma once

#include <SFML/Window/Mouse.hpp>
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/RenderTarget/Window.hpp"

namespace sgl
{
	using Button = sf::Mouse::Button;

	class Mouse
	{
		friend class Window;

		static void update();
	public:
		static bool isPressed(Button button);

		static ivec2 position();
		static ivec2 position(const ivec2& new_pos);

		static bool justPressed(Button button);
		static bool justReleased(Button button);
	};
}