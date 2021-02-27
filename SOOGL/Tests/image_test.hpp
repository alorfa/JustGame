#pragma once

#include "debug.hpp"

#include <stb/stb_image.h>
#include <fstream>
#include "SOOGL/Other/exceptions.hpp"
#include <filesystem>
#include "SOOGL/Other/types.hpp"
#include "SOOGL/Graphics/Image/Image.hpp"

using namespace sgl::exceptions;
using namespace sgl::types;

namespace sgl::tests
{
	inline void image_test1()
	{
		Image test_image;
		try
		{
			test_image.loadFromFile("image.jpg");
		}
		catch (file_error& f)
		{
			std::cout << "File " << f.path() << " is not found!" << std::endl;
			error_in_alf_test() = true;
			exit(1);
		}
		catch (image_error&)
		{
			std::cout << "Image is not correct: " << stbi_failure_reason() << std::endl;
			error_in_alf_test() = true;
			exit(1);
		}
		test_image.saveToFileJpg("image2.jpeg", 82);
		PRINT((int)test_image.type());
		system("image2.jpeg");

		clear_test();
	}
	inline void image_test2()
	{
		for (size_t i = 0; i < 100; i++)
		{
			Image image;
			try
			{
				image.loadFromFile("image2.jpg");
				image.saveToFileJpg("image2.jpg");
			}
			catch (...)
			{
				return;
			}
		}
	}
}