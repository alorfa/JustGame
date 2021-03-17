#include "RenderTarget.hpp"
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

	void RenderTarget::clear(const color4f& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RenderTarget::clear(const color3f& color)
	{
		glClearColor(color.r, color.g, color.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RenderTarget::clear(const color4b& color)
	{
		glClearColor(
			(float)color.r / 255.f,
			(float)color.g / 255.f,
			(float)color.b / 255.f,
			(float)color.a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void RenderTarget::clear(const color3b& color)
	{
		glClearColor(
			(float)color.r / 255.f,
			(float)color.g / 255.f,
			(float)color.b / 255.f,
			1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderTarget::drawArrays(DrawMode mode, int begin, int count)
	{
		glDrawArrays((GLenum)mode, begin, count);
	}
	void RenderTarget::drawIndexes(DrawMode mode, int count)
	{
		glDrawElements((GLenum)mode, count, GL_UNSIGNED_INT, nullptr);
	}
	void RenderTarget::drawIndexes(DrawMode mode, int count, uint gl_type)
	{
		glDrawElements((GLenum)mode, count, gl_type, nullptr);
	}

	uvec2 RenderTarget::default_framebuf_size;
}