#pragma once

#include "SOOGL/Graphics/Text.hpp"
#include "SOOGL/Render.hpp"
#include "SOOGL/Other/exceptions.hpp"

namespace sgl::tests
{
	inline int font_test()
	{
		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return -1;

		Font font;
		try {
			font.loadFromFile("fonts/Arial.ttf");
		} catch (file_error& e) {
			std::cout << "File " << e.path().c_str() << " not open!" << std::endl;
			return -1;
		}

		while (window.isOpen())
		{
			if (window.shouldClose())
				window.close();



			window.update();
		}
	}
}