#include "File.hpp"
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Other/exceptions.hpp"

namespace sgl
{
	using namespace types;
	using namespace exceptions;

	File::File(const std::filesystem::path& path, int flag)
	{
		open(path, flag);
	}

	File& File::open(const std::filesystem::path& path, int flag)
	{
		if (not std::filesystem::exists(path))
			throw file_error(path, file_error::not_found);

		uint std_flag = 0;
		if (flag & Flag::Read)
			std_flag |= std::ios_base::in;
		if (flag & Flag::Write)
			std_flag |= std::ios_base::out;
		if (flag & Flag::Add)
			std_flag |= std::ios_base::app;
		if (flag & Flag::Text)
			text_mode = true;
		else
			std_flag |= std::ios_base::binary;

		file.open(path, std_flag);
		if (not file.is_open())
			throw file_error(path, file_error::not_open);

		open_path = &path;
		return *this;
	}
	bool File::isOpen()
	{
		return file.is_open();
	}
	File& File::close()
	{
		file.close();
		return *this;
	}
}