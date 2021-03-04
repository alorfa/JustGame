#include "Mouse.hpp"

namespace sgl
{
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
}