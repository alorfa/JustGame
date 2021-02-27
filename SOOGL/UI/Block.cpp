#include "Block.hpp"

namespace sgl
{
	Block::~Block()
	{
		if (border)
			delete border;
	}
}