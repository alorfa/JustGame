#pragma once

#include "RenderTarget.hpp"
#include "SOOGL/Math/vec2.hpp"
#include <string>
#include "SOOGL/Math/rect_area.hpp"

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
		Window();
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

		ivec2 position() const;
		ivec2 position(const ivec2& new_pos);

		rect_area<int> area() const;

		const std::string& title() const;
		const std::string& title(const std::string& utf8string);

		uint frameLinit() const; 
		uint frameLinit(uint limit); 

		bool verticalSync() const;
		bool verticalSync(bool enable);

		bool isResized() const;
		bool isOpen() const;
		bool isFocused() const;
		bool shouldClose() const;

		void update();
	};
}