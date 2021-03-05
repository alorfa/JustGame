#include "SOOGL/Other/opengl.h"
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/System/User/Keyboard.hpp"
#include "SOOGL/System/User/Mouse.hpp"

namespace sgl
{
	namespace wnd
	{
		sf::Window* window;
		sf::Event* event;

		int windows_count = 0;
		uvec2 lim_min, lim_max;
		size_limit size_lim;
		std::string wnd_title;
		uint frame_limit = 0;
		bool vertical_sync = true;
	}
	using namespace wnd;

	Window::Window()
	{
		if (not window)
		{
			window = new sf::Window;
			event = new sf::Event;
		}
	}
	Window::~Window()
	{
		destroy();
	}
	bool Window::create(const uvec2& size, const std::string& title)
	{
		destroy();

		if (windows_count > 0)
			return false;

		window->create(sf::VideoMode(size.x, size.y), title, sf::Style::Default);
		glViewport(0, 0, (int)size.x, (int)size.y);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			window->close();
			return false;
		}

		windows_count++;
		return true;
	}
	void Window::destroy()
	{
		if (window->isOpen())
		{
			window->close();
			windows_count--;
		}
	}
	void Window::close()
	{
		will_be_closed = true;
	}
	uvec2 Window::size() const
	{
		auto out = window->getSize();
		return uvec2(out.x, out.y);
	}
	uvec2 Window::size(const uvec2& size)
	{
		window->setSize({ size.x, size.y });
		return size;
	}
	ivec2 Window::position() const
	{
		auto output = window->getPosition();
		return { output.x, output.y };
	}
	ivec2 Window::position(const ivec2& new_pos)
	{
		window->setPosition({ new_pos.x, new_pos.y });
		return new_pos;
	}

	rect_area<int> Window::area() const
	{
		auto left_top = position();
		return rect_area<int>(
			left_top, left_top + ivec2(size().x, size().y));
	}

	const std::string& Window::title() const
	{
		return wnd_title;
	}

	const std::string& Window::title(const std::string& utf8string)
	{
		wnd_title = utf8string;
		window->setTitle(utf8string);
		return wnd_title;
	}
	
	uint Window::frameLinit() const
	{
		return frame_limit;
	}
	uint Window::frameLinit(uint limit)
	{
		frame_limit = limit;
		window->setFramerateLimit(limit);
		return limit;
	}

	bool Window::verticalSync() const
	{
		return vertical_sync;
	}

	bool Window::verticalSync(bool enable)
	{
		window->setVerticalSyncEnabled(enable);
		return enable;
	}

	bool Window::isResized() const
	{
		return event->type == event->Resized;
	}

	bool Window::isOpen() const
	{
		return window->isOpen();
	}
	bool Window::isFocused() const
	{
		return window->hasFocus();
	}
	bool Window::shouldClose() const
	{
		return event->type == event->Closed;
	}
	void Window::update()
	{
		Keyboard::update();
		Mouse::update();

		window->pollEvent(*event);
		window->display();

		if (isResized())
		{
			auto size = this->size();
			glViewport(0, 0, (int)size.x, (int)size.y);
		}

		if (will_be_closed)
			destroy();
	}
}