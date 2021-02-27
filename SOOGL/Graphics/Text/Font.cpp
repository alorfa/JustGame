#include "Font.hpp"
#include "SOOGL/Other/exceptions.hpp"
#include "SOOGL/System/File.hpp"
#include "SOOGL/Other/opengl.h"
#include "SOOGL/Tests/debug.hpp"

namespace sgl
{
	using namespace exceptions;

	void Font::init()
	{
		if (FT_Init_FreeType(&ft))
			throw init_error();
	}

	Font::~Font()
	{
		FT_Done_Face(face);
	}

	void Font::createAllTextures()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

		auto addition_size = size();
		auto& char_map = font_data[addition_size];

		for (unsigned char ch = 0; ch < 128; ch++)
		{
			if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
			{
				err_chars.push_back(ch);
				continue;
			}
			auto& glyph = face->glyph;
			auto& bitmap = glyph->bitmap;

			CharTexture char_texture;
			char_texture.texture.create(
				{ bitmap.width, bitmap.rows },
				Image::Red,
				Image::Red,
				bitmap.buffer,
				Texture::Smooth | Texture::ClampToEdge);
			char_texture.bearing = { (uint)glyph->bitmap_left, (uint)glyph->bitmap_top };
			char_texture.advance = glyph->advance.x;

			char_map.insert(std::pair(ch, std::move(char_texture)));
		}
		PRINT(OGL_ERR_COUNT());
	}
	void Font::loadFromFile(const std::filesystem::path& path)
	{
		// This is to throw necessary exceptions
		File file;
		file.open(path);
		file.close();

		if (FT_New_Face(ft, path.u8string().c_str(), 0, &face))
			throw font_error(font_error::load_font);
	}
	uint Font::size(uint new_size)
	{
		FT_Set_Pixel_Sizes(face, 0, new_size);
		font_size = new_size;

		if (font_data.count(new_size) == 0) // elem is not exists
			createAllTextures();

		return new_size;
	}
	uint Font::size()
	{
		return font_size;
	}
	FT_Library Font::ft;
}