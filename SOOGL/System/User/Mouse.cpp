#include "Mouse.hpp"
#include <vector>

namespace sgl
{
	namespace
	{
		constexpr size_t BUTTON_COUNT = sf::Mouse::ButtonCount;

		std::vector<bool> keys(BUTTON_COUNT);
		std::vector<bool> press_keys(BUTTON_COUNT);
		std::vector<bool> release_keys(BUTTON_COUNT);
	}

	void Mouse::update()
	{
		for (size_t bt = 0; bt < BUTTON_COUNT; bt++)
		{
			bool keystate = sgl::Mouse::isPressed(Button(bt));
			press_keys[bt] = release_keys[bt] = false;
			if (keys[bt] == false)
			{
				keys[bt] = keystate;
				if (keystate)
					press_keys[bt] = true;
				continue;
			}
			else
			{
				keys[bt] = keystate;
				if (keystate == false)
					release_keys[bt] = true;
				continue;
			}
			keys[bt] = keystate;
		}
	}
	bool Mouse::isPressed(Button but)
	{
		return sf::Mouse::isButtonPressed(but);
	}

	ivec2 Mouse::position()
	{
		auto output = sf::Mouse::getPosition();
		return ivec2(output.x, output.y);
	}
	ivec2 Mouse::position(const ivec2& new_pos)
	{
		sf::Mouse::setPosition({ new_pos.x, new_pos.y });
		return position();
	}

	bool Mouse::justPressed(Button button)
	{
		return press_keys[button];
	}
	bool Mouse::justReleased(Button button)
	{
		return release_keys[button];
	}
}