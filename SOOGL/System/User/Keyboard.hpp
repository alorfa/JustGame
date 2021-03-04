#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "SOOGL/RenderTarget/Window.hpp"

namespace sgl
{
	using Key = sf::Keyboard::Key;

	class Keyboard
	{
		static void update();

		friend class Window;
	public:
		static bool isPressed(Key key);

		static bool justPressed(Key key);
		static bool justReleased(Key key);
	};
}