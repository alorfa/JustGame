#include "Texture.hpp"
#include "SOOGL/Other/opengl.h"
#include "SOOGL/Tests/debug.hpp"

namespace sgl
{
	GLenum toOglType(int image_comp_count)
	{
		switch (image_comp_count)
		{
		case 1:
			return GL_RED;
		//case 2:
		//	return GL_DEPTH;
		case 3:
			return GL_RGB;
		case 4:
			return GL_RGBA;
		}
		return 0;
	}
	GLenum toOglWrap(int wrap_type)
	{
		if (wrap_type & Texture::Flag::Repeat)
			return GL_REPEAT;
		if (wrap_type & Texture::Flag::MirroredRepeat)
			return GL_MIRRORED_REPEAT;
		if (wrap_type & Texture::Flag::ClampToEdge)
			return GL_CLAMP_TO_EDGE;
		if (wrap_type & Texture::Flag::ClampToBorder)
			return GL_CLAMP_TO_BORDER;
		return GL_REPEAT;
	}

	void Texture::createTexture()
	{
		if (id == 0)
			glGenTextures(1, &id);
	}
	void Texture::deleteTexture()
	{
		if (id)
			glDeleteTextures(1, &id);
	}

	Texture::Texture()
		: m_size(), id(0) {}

	Texture::Texture(Texture&& other) noexcept
	{
		this->operator=(std::move(other));
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		deleteTexture();

		id = other.id;
		m_size = other.m_size;

		other.id = 0;

		return *this;
	}

	Texture::~Texture()
    {
		deleteTexture();
	}

	uint Texture::nativeHandle() const
	{
		return id;
	}

	void Texture::activate() const
	{
		glActiveTexture(GL_TEXTURE0 + id);
		glBindTexture(GL_TEXTURE_2D, id);
	}

    void Texture::create(const uvec2& size, Image::Type out_format, Image::Type in_format, 
		const void* data, int flag)
    {
		createTexture();

		this->m_size = size;

		glBindTexture(GL_TEXTURE_2D, id);

		glTexImage2D(GL_TEXTURE_2D, 0, toOglType(out_format),
			(GLsizei)size.x, (GLsizei)size.y,
			0, toOglType(in_format), GL_UNSIGNED_BYTE, data);

		if (OGL_ERROR())
			PRINT(out_format);

		if (flag & Flag::Smooth) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, toOglWrap(flag));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, toOglWrap(flag));
    }

	void Texture::loadFromImage(const Image& image, Flag flag)
	{
		create(image.size(), image.type(), Image::RGB_Alpha, image.data<void>(), flag);
	}

	void Texture::loadFromMemory(const ubyte* data, size_t size, Flag flag)
	{
		Image image;
		image.loadFromMemory(data, size);
		loadFromImage(image, flag);
	}

	void Texture::loadFromFile(const std::filesystem::path& path, Flag flag)
	{
		Image image;
		image.loadFromFile(path);
		loadFromImage(image, flag);
	}

}