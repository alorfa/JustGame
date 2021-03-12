#pragma once

#include "SOOGL/Init.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Other/exceptions.hpp"

#include "SOOGL/System/Time/Time.hpp"
#include "SOOGL/System/Time/Clock.hpp"

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Shader/Shader.hpp"
#include "SOOGL/Graphics/Shader/ShaderCompiler.hpp"
#include "SOOGL/Graphics/Transform/Camera2D.hpp"

#include "Game/Object/Color.hpp"

#include "SOOGL/Graphics/Blend.hpp"
#include "SOOGL/Tests/debug.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/System/User/Mouse.hpp"
#include "SOOGL/Other/print_primitives.hpp"

#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/RenderTarget/FrameBuffer.hpp"
#include "SOOGL/RenderTarget/RenderBuffer.hpp"

#include "SOOGL/Tests/Rectangle.hpp"

namespace tests
{
	using namespace sgl;

	int main_test()
	{
		Init Initializer;

		Blend::activate(Blend::Default);

		Clock clock;

		Window window;
		if (not window.create({ 800, 800 }, "Title"))
			return -1;

		Texture texture;
		Shader to_fbo_shader;
		try
		{
			texture.loadFromFile("asd.jpg");

			ShaderCompiler compiler;
			compiler.loadFromFile("shaders/vertex.vsh", Shader::Vertex);
			compiler.loadFromFile("shaders/fragment.fsh", Shader::Fragment);
			to_fbo_shader = compiler.link();
		}
		catch (shader_error& err)
		{
			std::cout << "Shader not load: " << err.message() << std::endl;
			exit(-1);
		}
		catch (image_error&)
		{
			std::cout << "Texture not load" << std::endl;
			exit(-1);
		}
		catch (file_error&)
		{
			std::cout << "File not found" << std::endl;
			exit(-1);
		}

		window.frameLinit(60);

		Camera2D camera;
		camera.move(0.5f, 0.5f);

		double d_delta = 0.0;
		float delta = 0.f;

		gd::Color color;
		color.change({ 0.8f, 0.1f, 0.5f, 1.f });

		PRINT(RenderBuffer::isValid());
		FrameBuffer frame_buffer;
		frame_buffer.create({ 800, 800 });
		frame_buffer.activate();
		PRINT(frame_buffer.isValid());
		frame_buffer.deactivate();
		PRINT(frame_buffer.isValid());

		sgl::tests::Rectangle::init();
		sgl::tests::Rectangle r1(texture);
		sgl::tests::Rectangle r2(frame_buffer.texture());

		while (window.isOpen())
		{
			d_delta = clock.update();
			delta = float(d_delta); 

			window.clear(color3f{ 0.5f, 0.5f, 0.5f });

			if (window.shouldClose())
				window.close();

			PRINTR(sgl::Mouse::onWindow(window));

			if (window.isFocused())
			{
				if (Keyboard::justPressed(Key::Left))
					color.change({ 0.3f, 0.3f, 0.6f, 1.f }, 0.3);
				if (Keyboard::justReleased(Key::Left))
					color.change({ 0.5f, 0.3f, 0.3f, 1.f }, 0.3);

				if (Mouse::onWindow(window))
				{
					if (Mouse::justPressed(Button::Left))
						color.change({ 0.4f, 0.6f, 1.f, 0.1f }, 0.3);
					if (Mouse::justReleased(Button::Left))
						color.change({ 0.0f, 0.0f, 0.f, 1.f }, 0.3);
				}

				if (Keyboard::isPressed(Key::Left)) {
					r1.move({ -0.5f * delta, 0 });
					//r2.move({ 0, -0.5f * delta });
				}
				if (Keyboard::isPressed(Key::Right)) {
					r1.move({ 0.5f * delta, 0 });
					//r2.move({ 0, 0.5f * delta });
				}
			}
			color.update(d_delta);

			window.clearBuffer(Window::ColorBuf);
			window.clear(color3f());

			frame_buffer.activate();
			r1.draw(camera);
			frame_buffer.deactivate();
			r2.draw(camera);

			window.update();
		}

		return 0;
	}
}