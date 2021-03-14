#include "SOOGL/Graphics/Image/Image.hpp"
#include <algorithm>
//#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>
#include "SOOGL/Other/exceptions.hpp"
#include <fstream>
#include <memory>
#include "SOOGL/System/File.hpp"

using namespace sgl::exceptions;
using namespace sgl::types;

namespace sgl
{
	Image::Image()
		: m_size(), m_type(Image::Type::Undefined), m_data(nullptr) {}

	Image::Image(const Image& other)
		: m_data(nullptr) // for correct cleaning
	{
		this->operator=(other);
	}
	Image::Image(Image&& other) noexcept
	{
		this->operator=(std::move(other));
	}
	Image& Image::operator=(const Image& other)
	{
		create(other.m_size, other.m_type, other.m_data);

		return *this;
	}
	Image& Image::operator=(Image&& other) noexcept
	{
		useImageData(other.m_size, other.m_type, other.m_data);
		other.m_data = nullptr;

		return *this;
	}
	Image::~Image()
	{
		clear();
	}

	void Image::clear()
	{
		if (this->m_data) 
		{
			delete m_data;
			m_size.x = 0;
			m_size.y = 0;
			m_type = Type::Undefined;
		}
		this->m_data = nullptr;
	}
	void Image::useImageData(const uvec2& size, Image::Type type, ubyte* data)
	{
		clear();

		this->m_size = size;
		this->m_type = type;
		this->m_data = data;
	}
	void Image::create(const uvec2& size, Image::Type type, const ubyte* data)
	{
		clear();

		this->m_size = size;
		this->m_type = type;
		size_t new_data_size = size.x * size.y * type;
		if (new_data_size)
		{
			this->m_data = new ubyte[new_data_size];
			memcpy(this->m_data, data, new_data_size);
		}
	}

	void Image::loadFromMemory(const ubyte* data, size_t size)
	{
		//stbi_set_flip_vertically_on_load(true);
		if (data && size)
		{
			int x, y, components;
			uint8* image_data = stbi_load_from_memory(data, (int)size, &x, &y, &components, STBI_rgb_alpha);
			if (image_data)
			{
				useImageData(uvec2(x, y), (Type)components, image_data);
				return;
			}
		}
		throw image_error();
	}

	void Image::loadFromFile(const std::filesystem::path& path)
	{
		size_t length = 0;
		ubyte* file_data = nullptr;

		File file;
		file.open(path).readAllBytes<ubyte>(file_data, length);

		std::unique_ptr<ubyte> cleaner(file_data);

		loadFromMemory(file_data, length);
	}

	void Image::saveToFileBmp(const std::filesystem::path& path) const
	{
		stbi_write_bmp(path.string().c_str(),
			int(m_size.x), int(m_size.y),
			m_type, (void*)m_data);
	}
	void Image::saveToFileTga(const std::filesystem::path& path) const
	{
		stbi_write_tga(path.string().c_str(),
			int(m_size.x), int(m_size.y),
			m_type, (void*)m_data);
	}
	void Image::saveToFilePng(const std::filesystem::path& path) const
	{
		stbi_write_png(path.string().c_str(),
			int(m_size.x), int(m_size.y),
			m_type, (void*)m_data, 0);
	}
	void Image::saveToFileJpg(const std::filesystem::path& path, uint quality) const
	{
		stbi_write_jpg(path.string().c_str(),
			int(m_size.x), int(m_size.y),
			m_type, (void*)m_data, (int)quality);
	}

	color3b& Image::pixel_rgb(const uvec2& pixel_pos)
	{
		color3b* ptr = (color3b*)m_data;
		return ptr[pixel_pos.y * m_size.x + pixel_pos.x];
	}

	color4b& Image::pixel_rgba(const uvec2& pixel_pos)
	{
		color4b* ptr = (color4b*)m_data;
		return ptr[pixel_pos.y * m_size.x + pixel_pos.x];
	}
}