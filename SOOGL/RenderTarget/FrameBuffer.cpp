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
		glGenFramebuffers(1, &id);
	}
	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &id);
	}
	void FrameBuffer::create(uvec2 size, Type type)
	{
		this->type = type;
		r_texture.create(size, Image::RGB, Image::RGB, nullptr, Texture::Nothing);

		bind(type, id);

		glFramebufferTexture2D(toOglType(type), GL_COLOR_ATTACHMENT0, 
			GL_TEXTURE_2D, r_texture.nativeHandle(), 0);

		bind(type, 0);
	}
	void FrameBuffer::activate() const
	{
		RenderTarget::viewport(texture().size());
		bind(type, id);
	}
	void FrameBuffer::deactivate() const
	{
		RenderTarget::viewport(RenderTarget::default_framebuf_size);
		bind(type, 0);
	}
	bool FrameBuffer::isValid()
	{
		return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	}
}