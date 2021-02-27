#include "Blend.hpp"
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	GLenum toOglBlendMode(Blend::Mode factor)
	{
		switch (factor)
		{
		case Blend::Mode::SrcAlpha: return GL_SRC_ALPHA;
		case Blend::Mode::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
		}
		return GL_ONE_MINUS_SRC_ALPHA;
	}
	void Blend::activate(Mode sfactor, Mode dfactor)
	{
		glEnable(GL_BLEND);
		glBlendFunc(toOglBlendMode(sfactor), toOglBlendMode(dfactor));
	}
	void Blend::activate(Mode dfactor)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, toOglBlendMode(dfactor));
	}
}