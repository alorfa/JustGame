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

		/* Returns the position in pixels of the cursor on the screen. Left top point is [0, 0],
		* right bottom is [monitor width, monitor height]
		*/
		static ivec2 position();

		/* Sets the position in pixels of the cursor on the screen. Left top point is [0, 0],
		* right bottom is [monitor width, monitor height]
		*/
		static ivec2 position(const ivec2& new_pos);

		/* Returns the position in pixels of the cursor relative the specified window.
		* Left top point is [0, 0], right bottom is [window width, window height]
		*/
		static ivec2 position(const Window& relativeTo);

		/* Sets the position in pixels of the cursor relative the specified window. 
		* Left top point is [0, 0], right bottom is [window width, window height]
		*/
		static ivec2 position(const ivec2& new_pos, const Window& relativeTo);

		static bool onWindow(const Window& window);

		static bool justPressed(Button button);
		static bool justReleased(Button button);


	};
}