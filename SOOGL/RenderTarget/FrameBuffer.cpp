#include "FrameBuffer.hpp"
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	GLenum toOglType(FrameBuffer::Type type) 
	{
		switch (type)
		{
		case FrameBuffer::Default: return GL_FRAMEBUFFER;
		case FrameBuffer::Read: return GL_READ_FRAMEBUFFER;
		case FrameBuffer::Draw: return GL_DRAW_FRAMEBUFFER;
		}
		return 0;
	}

	void bind(FrameBuffer::Type type, uint id)
	{
		glBindFramebuffer(toOglType(type), id);
	}

	FrameBuffer::FrameBuffer()
		: type(FrameBuffer::Nothing)
	{
		glGenFramebuffers(1, &m_id);
	}
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_id);
	}
	void FrameBuffer::create(uvec2 size, Type type)
	{
		this->type = type;
		texture.create(size, Image::RGB, Image::RGB, nullptr, Texture::Smooth); 
		bind(type, m_id); 
		glFramebufferTexture2D(toOglType(type), GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id(), 0);
		bind(type, 0);
	}
	bool FrameBuffer::isValid()
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}
}