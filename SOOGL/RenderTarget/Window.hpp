#pragma once

#include "SOOGL/Other/opengl.h"
#include "GLFW/glfw3.h"
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/RenderTarget/RenderTarget.hpp"
#include "SOOGL/System/FpsManager.hpp"

namespace sgl
{
	using namespace vec;

	/* This class supports only one window!!! You can't create more than one window!!!
	*/

	class Window : public RenderTarget
	{
		GLFWwindow* window = nullptr;

		bool will_be_closed = false;
	public:
		inline Window() = default;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window();

		bool create(const vec2_size& size);
		void destroy();
		void close();

		vec2_size size();
		void resize(const vec2_size& size);

		bool isResized();
		bool isOpen();
		bool shouldClose();

		void update();
	};
}