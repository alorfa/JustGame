#include "SOOGL/RenderTarget/Window.hpp"

namespace sgl
{
	bool window_is_resized = false;
	int windows_count = 0;


	Window::~Window()
	{
		destroy();

		glfwTerminate();
	}
	bool Window::create(const vec2_size& size)
	{
		destroy();

		if (windows_count > 0)
			return false;

		if (not glfwInit())
			return false;

		window = glfwCreateWindow(int(size.x), int(size.y), "a", nullptr, nullptr);
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
	vec2_size Window::size()
	{
		vec2_size output;
		ivec2 cur_size;

		glfwGetWindowSize(window, &cur_size.x, &cur_size.y);

		output.x = cur_size.x;
		output.y = cur_size.y;

		return output;
	}
	void Window::resize(const vec2_size& size)
	{
		glfwSetWindowSize(window, (int)size.x, (int)size.y);
	}
	bool Window::isResized()
	{
		return window_is_resized;
	}

	bool Window::isOpen()
	{
		return (bool)window;
	}
	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	void Window::update()
	{
		window_is_resized = false;

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (will_be_closed)
			destroy();
	}
}