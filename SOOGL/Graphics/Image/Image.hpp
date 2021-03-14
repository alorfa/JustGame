#pragma once

#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Graphics/color.hpp"
#include <filesystem>

namespace sgl
{
	using vec::uvec2;
	using types::ubyte;
	using types::uint;
	using namespace color;

	class Image
	{
	public:
		// also this type, when cast to int, shows the count of color components
		enum Type : int { Undefined = 0, Red, Depth_Alpha, RGB = 3, RGB_Alpha };
	private:
		uvec2 m_size;
		Type m_type;
		ubyte* m_data;
	public:
		Image();
		Image(const Image& other);
		Image(Image&& other) noexcept;
		Image& operator=(const Image& other);
		Image& operator=(Image&& other) noexcept;
		~Image();

		void clear();

		/* Just clears and copies new size, type and pointer to the image data(not the 
		* image data itself). Be careful with this method*/
		void useImageData(const uvec2& size, Image::Type type, ubyte* data);
		/* Creates a complete copy of the image. Absolutely safe method*/
		void create(const uvec2& size, Image::Type type, const ubyte* data);

		// Parse image data of any format and creates the image
		void loadFromMemory(const ubyte* data, size_t size);
		void loadFromFile(const std::filesystem::path& path);

		void saveToFileBmp(const std::filesystem::path& path) const;
		void saveToFileTga(const std::filesystem::path& path) const;
		void saveToFilePng(const std::filesystem::path& path) const;
		void saveToFileJpg(const std::filesystem::path& path, uint quality = 90) const;

		template <typename T>
		const T* data() const {
			return (T*)m_data;
		}
		template <typename T>
		T* data() {
			return (T*)m_data;
		}
		inline bool isValid() const {
			return (bool)m_data;
		}
		inline Type type() const {
			return m_type;
		}
		inline const uvec2& size() const {
			return m_size;
		}

		color3b& pixel_rgb(const uvec2& pixel_pos);
		color4b& pixel_rgba(const uvec2& pixel_pos);
	};
}