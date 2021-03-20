#include "Camera2D.hpp"
#include <cmath>

namespace sgl
{
	const Camera2D Camera2D::by_default;

	const Transform2D& Camera2D::transform() const
	{
		return ((const Transformable2D*)this)->transform();
	}
}