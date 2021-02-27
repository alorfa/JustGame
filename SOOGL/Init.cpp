#include "Init.hpp"
#include "SOOGL/Math/trig.hpp"
#include "SOOGL/Graphics/Text/Font.hpp"

namespace sgl
{
	Init::Init()
	{
		Font::init();
	}
	Init::~Init()
	{
		FT_Done_FreeType(Font::ft);
	}
}
