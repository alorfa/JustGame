#include "SOOGL/RenderTarget/RenderTarget.hpp"
#include "SOOGL/Other/opengl.h"

namespace sgl
{
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

		if ((uint)buf & (uint)ClearBuf::Color)
			output |= GL_COLOR_BUFFER_BIT;
		if ((uint)buf & (uint)ClearBuf::Depth)
			output |= GL_DEPTH_BUFFER_BIT;

		glClear(output);
	}
}