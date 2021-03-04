#include "Keyboard.hpp"
#include <vector>

constexpr size_t KEY_COUNT = sf::Keyboard::KeyCount;

namespace sgl
{
	namespace
	{
		std::vector<bool> keys(KEY_COUNT);
		std::vector<bool> press_keys(KEY_COUNT);
		std::vector<bool> release_keys(KEY_COUNT);
	}

	void Keyboard::update()
	{
		for (size_t key = 0; key < KEY_COUNT; key++)
		{
			bool keystate = sgl::Keyboard::isPressed(Key(key));
			press_keys[key] = release_keys[key] = false;
			if (keys[key] == false)
			{
				keys[key] = keystate;
				if (keystate)
					press_keys[key] = true;
				continue;
			}
			else
			{
				keys[key] = keystate;
				if (keystate == false)
					release_keys[key] = true;
				continue;
			}
			keys[key] = keystate;
		}
	}
	bool Keyboard::isPressed(Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}
	bool Keyboard::justPressed(sgl::Key key)
	{
		/*
		bool keystate = sgl::Keyboard::isPressed(key);
		if (keys[key] == false)
		{
			keys[key] = keystate;
			if (keystate)
				return true;
		}
		keys[key] = keystate;
		return false;/**/
		return press_keys[key];
	}
	bool Keyboard::justReleased(Key key)
	{
		/*
		bool keystate = sgl::Keyboard::isPressed(key);
		if (keys[key] == true)
		{
			keys[key] = keystate;
			if (keystate == false)
				return true;
		}
		keys[key] = keystate;
		return false;/**/
		return release_keys[key];
	}
}