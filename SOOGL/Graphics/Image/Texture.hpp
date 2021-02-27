#pragma once

#include "Image.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	using namespace types;
	using namespace vec;

	class Texture
	{
		uint id;
		uvec2 m_size;

		void createTexture();
		void deleteTexture();
	public:
		enum Flag : int
		{
			Nothing = 0,
			Smooth = 1 << 0,
			Repeat = 1 << 1,
			MirroredRepeat = 1 << 2,
			ClampToEdge = 1 << 3,
			ClampToBorder = 1 << 4
		};

		Texture();
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
		~Texture();

		void create(const uvec2& size, Image::Type out_format, Image::Type in_format, 
			const void* data, int settings = Smooth);
		void loadFromImage(const Image& image, Flag flag = Smooth);
		void loadFromMemory(const ubyte* data, size_t size, Flag flag = Smooth);
		void loadFromFile(const std::filesystem::path& path, Flag flag = Smooth);

		uint nativeHandle() const;

		void activate() const;

		inline const uvec2& size() const {
			return m_size;
		}
		inline bool isValid() const {
			return m_size.x && m_size.y;
		}
	};
}