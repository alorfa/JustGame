#pragma once

#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/RenderTarget/RenderTarget.hpp"
#include <string>

namespace sgl
{
	struct size_limit
	{
		uvec2 min, max;
	};

	/* This class supports only one window!!! You can't create more than one window!!!
	*/
	class Window : public RenderTarget
	{
		bool will_be_closed = false;
	public:
		inline Window() = default;
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window();

		bool create(const uvec2& size, const std::string& title);
		void destroy();
		void close();

		uvec2 size() const;
		uvec2 size(const uvec2& size);

		const size_limit& sizeLimit() const;
		const size_limit& sizeLimit(const uvec2& min, const uvec2& max);

		uvec2 aspectRatio() const;
		uvec2 aspectRatio(const uvec2& ratio);

		uvec2 position() const;
		uvec2 position(const uvec2& new_pos);

		const std::string& title() const;
		const std::string& title(const std::string& utf8string);

		bool isResized() const;
		bool isOpen() const;
		bool isFocused() const;
		bool shouldClose() const;

		void update();
	};
}