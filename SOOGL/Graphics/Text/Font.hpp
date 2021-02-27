#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H  
#include <filesystem>
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Math/vec2.hpp"
#include <map>
#include <vector>
#include "SOOGL/Graphics/Image/Texture.hpp"

#include "SOOGL/Init.hpp"

namespace sgl
{
	using namespace types;
	using namespace vec;

	class Font
	{
	public:
		struct CharTexture
		{
			sgl::Texture texture;
			uvec2 bearing;
			uint advance = 0;
		};
		using GlyphMap = std::map<char, CharTexture>;
	private:
		static FT_Library ft;

		friend class Init;
		static void init();

		FT_Face face = nullptr;

		std::map<uint, GlyphMap> font_data;
		std::vector<char> err_chars;
		uint font_size = 0;

		void createAllTextures();
	public:
		Font() = default;
		~Font();

		void loadFromFile(const std::filesystem::path& path);

		uint size(uint new_size);
		uint size();

		bool hasErrors() const {
			return not err_chars.empty();
		}
		const std::vector<char> failedChars() const {
			return err_chars;
		}

		const GlyphMap& glyphMap() const {
			return font_data.at(font_size);
		}
	};
}