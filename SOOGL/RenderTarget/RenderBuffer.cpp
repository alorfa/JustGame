#pragma once

#include "RenderBuffer.hpp"
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	RenderBuffer::RenderBuffer()
	{
		glGenRenderbuffers(1, &id);
	}
	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &id);
	}
	void RenderBuffer::create(uvec2 size)
	{
		frame_buffer.create(size);

		activate();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)size.x, (int)size.y);
		deactivate();

		frame_buffer.activate();
		// bind render buffer to frame buffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, id); 
		frame_buffer.deactivate();
	}
	bool RenderBuffer::isValid()
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}
	void RenderBuffer::activate() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, id);
	}
	void RenderBuffer::deactivate()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}