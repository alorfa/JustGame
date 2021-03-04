#include "SOOGL/Other/opengl.h"
#include "GLFW/glfw3.h"
#include "SOOGL/RenderTarget/Window.hpp"
#include "SOOGL/System/User/Keyboard.hpp"

namespace sgl
{
	GLFWwindow* window = nullptr;

	bool window_is_resized = false;
	int windows_count = 0;
	uvec2 lim_min, lim_max;
	size_limit size_lim;
	std::string wnd_title;

	Window::~Window()
	{
		destroy();

		glfwTerminate();
	}
	bool Window::create(const uvec2& size, const std::string& title)
	{
		destroy();

		if (windows_count > 0)
			return false;

		if (not glfwInit())
			return false;

		window = glfwCreateWindow(int(size.x), int(size.y), title.c_str(), nullptr, nullptr);
		// glGetError(); // 
		if (not window)
			return false;

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK)
			return false;

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				glViewport(0, 0, width, height);
				window_is_resized = true;
			});

		windows_count++;
		return true;
	}
	void Window::destroy()
	{
		if (window)
		{
			glfwDestroyWindow(window);
			windows_count--;
		}
		window = nullptr;
	}
	void Window::close()
	{
		will_be_closed = true;
	}
	uvec2 Window::size() const
	{
		uvec2 output;
		ivec2 cur_size;

		glfwGetWindowSize(window, &cur_size.x, &cur_size.y);

		output.x = cur_size.x;
		output.y = cur_size.y;

		return output;
	}
	uvec2 Window::size(const uvec2& size)
	{
		glfwSetWindowSize(window, (int)size.x, (int)size.y);
		return size;
	}

	const size_limit& Window::sizeLimit() const
	{
		return size_lim;
	}
	const size_limit& Window::sizeLimit(const uvec2& min, const uvec2& max)
	{
		size_lim.min = min;
		size_lim.max = max;

		int values[4];
		values[0] = (int)min.x;
		values[1] = (int)min.y;
		values[2] = (int)max.x;
		values[3] = (int)max.y;
		for (int& v : values)
			if (v == 0) v = GLFW_DONT_CARE;

		glfwSetWindowSizeLimits(window, values[0], values[1], values[2], values[3]);
		return sizeLimit();
	}	

	uvec2 Window::aspectRatio() const
	{
		return { 0, 0 };
	}
	uvec2 Window::aspectRatio(const uvec2& ratio)
	{
		ivec2 rat(ratio.x, ratio.y);
		if (rat.x == 0)
			rat.x = GLFW_DONT_CARE;
		if (rat.y == 0)
			rat.y = GLFW_DONT_CARE;

		glfwSetWindowAspectRatio(window, rat.x, rat.y);
		return ratio;
	}

	uvec2 Window::position() const
	{
		ivec2 output;
		glfwGetWindowPos(window, &output.x, &output.y);
		return { (uint)output.x, (uint)output.y };
	}
	uvec2 Window::position(const uvec2& new_pos)
	{
		glfwSetWindowPos(window, new_pos.x, new_pos.y);
		return new_pos;
	}

	const std::string& Window::title() const
	{
		return wnd_title;
	}

	const std::string& Window::title(const std::string& utf8string)
	{
		wnd_title = utf8string;
		glfwSetWindowTitle(window, utf8string.c_str());
		return wnd_title;
	}

	bool Window::isResized() const
	{
		return window_is_resized;
	}

	bool Window::isOpen() const
	{
		return (bool)window;
	}
	bool Window::isFocused() const
	{
		return glfwGetWindowAttrib(window, GLFW_FOCUSED);
	}
	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(window);
	}
	void Window::update()
	{
		Keyboard::update();

		window_is_resized = false;

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (will_be_closed)
			destroy();
	}
}