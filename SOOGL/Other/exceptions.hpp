#pragma once

#include <exception>
#include <filesystem>

namespace sgl
{
	class soogl_exception : public std::exception {};

	class init_error : public soogl_exception {};

	class file_error : public soogl_exception
	{
	public:
		enum Error { undefined, not_found, not_open, is_empty };
	private:
		std::filesystem::path m_path;
		Error m_error;
	public:
		inline file_error(const std::filesystem::path& path, Error error = undefined)
			: m_path(path), m_error(error) {}

		inline const std::filesystem::path& path() const {
			return m_path;
		}
		inline Error error() const {
			return m_error;
		}
	};
	class image_error : public soogl_exception {};

	class shader_error : public soogl_exception
	{
		std::string error_message;
	public:
		inline shader_error(const std::string& msg)
			: error_message(msg) {}

		inline const std::string& message() const {
			return error_message;
		}
	};

	class font_error : public soogl_exception
	{
	public:
		enum Error { undefined, load_font, load_glyph };
	private:
		Error err;
	public:
		inline font_error(Error err) {
			this->err = err;
		}
		inline Error error() const {
			return err;
		}
	};

	namespace exceptions
	{
		using namespace sgl;
	}
	namespace primitives
	{
		using namespace sgl;
	}
}