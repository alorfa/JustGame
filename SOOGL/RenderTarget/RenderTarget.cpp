#include "SOOGL/RenderTarget/RenderTarget.hpp"
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	void RenderTarget::viewport(uvec2 size)
	{
		glViewport(0, 0, (int)size.x, (int)size.y);
	}
	void RenderTarget::viewport(uvec2 begin, uvec2 end)
	{
		glViewport(int(begin.x), int(begin.y), int(end.x), int(end.y));
	}
	void RenderTarget::clear(const color3f& color)
	{
		glClearColor(color.r, color.g, color.b, 1.f);
	}
	void RenderTarget::clear(const color4f& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void RenderTarget::clear(const color3b& color)
	{
		glClearColor(
			(float)color.r / 255.f,
			(float)color.g / 255.f,
			(float)color.b / 255.f,
			1.f);
	}
	void RenderTarget::clear(const color4b& color)
	{
		glClearColor(
			(float)color.r / 255.f, 
			(float)color.g / 255.f,
			(float)color.b / 255.f,
			(float)color.a / 255.f);
	}

	void RenderTarget::clearBuffer(ClearBuf buf)
	{
		GLbitfield output = 0;

		if (buf & ColorBuf)
			output |= GL_COLOR_BUFFER_BIT;
		if (buf & DepthBuf)
			output |= GL_DEPTH_BUFFER_BIT;

		glClear(output);
	}
	uvec2 RenderTarget::default_framebuf_size;
}