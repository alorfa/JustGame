#pragma once

#include <SFML/Graphics.hpp>
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Render/Window.hpp"
#include "SOOGL/System/Time/Clock.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"

namespace sgl::tests
{
	inline int speed_test_soogl_and_sfml()
	{
		Window window;
		if (not window.create({ 800, 800 }, "title"))
			return -1;

		Texture texture;
		try {
			texture.loadFromFile("asd.jpg");
		} catch (...) {
			return -1;
		}



		while (window.isOpen())
		{
			if (window.shouldClose())
				window.close();



			window.update();
		}

		return 0;
	}
}