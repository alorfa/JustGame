#pragma once

#include "SOOGL/System/Time/Time.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Init.hpp"
#include "SOOGL/Math/trig.hpp"
#include "SOOGL/System/Time/Clock.hpp"
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"
#include "Game/Object/Color.hpp"
#include "SOOGL/Graphics/Blend.hpp"
#include "SOOGL/Tests/debug.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/System/User/Mouse.hpp"
#include "SOOGL/Other/print_primitives.hpp"
#include <Windows.h>
#include "GLFW/glfw3.h"
#include <SFML/Graphics.hpp>

namespace tests
{
	using namespace sgl::primitives;

	int main_test()
	{
		sgl::Init Initializer;

		sgl::Blend::activate(sgl::Blend::Default);

		Clock clock;

		sgl::Window window;
		if (not window.create({ 800, 800 }, "Title"))
			return -1;

		window.frameLinit(60);

		sgl::VertexBuffer2f vbuf;
		vbuf.changeData() = {
			{0.f, 0.f},
			{1.f, 0.f},
			{1.f, 1.f},
			{0.f, 1.f}
		};

		sgl::Camera2D camera;
		camera.move(0.5f, 0.5f);

		double d_delta = 0.0;
		float delta = 0.f;

		gd::Color color;
		color.change({ 0.8f, 0.1f, 0.5f, 1.f });

		while (window.isOpen())
		{
			d_delta = clock.update();
			delta = float(delta);

			window.clear(color3f{ 0.5f, 0.5f, 0.5f });

			if (window.shouldClose())
				window.close();

			PRINTR(sgl::Mouse::onWindow(window));

			if (window.isFocused())
			{
				if (sgl::Keyboard::justPressed(sgl::Key::Left))
					color.change({ 0.3f, 0.3f, 0.6f, 1.f }, 0.3);
				if (sgl::Keyboard::justReleased(sgl::Key::Left))
					color.change({ 0.5f, 0.3f, 0.3f, 1.f }, 0.3);

				if (sgl::Mouse::onWindow(window))
				{
					if (sgl::Mouse::justPressed(sgl::Button::Left))
						color.change({ 0.4f, 0.6f, 1.f, 0.1f }, 0.3);
					if (sgl::Mouse::justReleased(sgl::Button::Left))
						color.change({ 0.0f, 0.0f, 0.f, 1.f }, 0.3);
				}
			}
			color.update(d_delta);

			const sgl::Shader* shader = sgl::Shader::get(sgl::Vert2b | sgl::Col4u);
			if (not shader)
				continue;

			shader->setUniform(shader->location("transform"), camera.matrix());
			shader->setUniform(shader->location("color"), color.color());
			//PRINTR((fvec4)color.color());
			shader->activate();

			vbuf.activate(0);
			vbuf.drawArrays(sgl::DrawMode::TriangleFan);
			vbuf.deactivate(0);

			window.update();
		}

		return 0;
	}
}