#pragma once

#include <string>

namespace sgl
{
	class ShaderCreater
	{
	public:
		// returns empty string if flags is not correct
		static std::string createVertex(int shader);
		// returns empty string if flags is not correct
		static std::string createFragment(int shader);
	};
}