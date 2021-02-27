#pragma once

#include <fstream>
#include <filesystem>
#include "SOOGL/Other/exceptions.hpp"

namespace sgl
{
	class File
	{
		std::fstream file;
		const std::filesystem::path* open_path = nullptr;
		bool text_mode = false;
	public:
		File() = default;
		File(const File&) = delete;
		File& operator=(const File&) = delete;
		File(File&&) = default;
		File& operator=(File&&) = default;
		~File() = default; 
		
		enum Flag : int
		{
			Read = 1 << 0,
			Write = 1 << 1,
			Add = 1 << 2,
			Text = 1 << 3
		};
		File(const std::filesystem::path& path, int flag = Flag::Read);
		File& open(const std::filesystem::path& path, int flag = Flag::Read);
		bool isOpen();
		File& close();

		template <typename T>
		File& readAllBytes(T*& out_data, size_t& out_size)
		{
			using namespace sgl::exceptions;

			if (not isOpen())
			{
				out_data = nullptr;
				out_size = 0;
				return *this;
			}

			file.seekg(0, file.end);
			out_size = file.tellg();
			file.seekg(0, file.beg);

			if (out_size == 0)
			{
				out_data = nullptr;
				throw file_error(*open_path, file_error::is_empty);
			}

			out_data = (T*)new char[out_size + (int)text_mode]; // extra byte if text_mode
			if (text_mode)
				out_data[out_size] = '\0';

			file.read((char*)out_data, out_size);

			return *this;
		}
	};
}