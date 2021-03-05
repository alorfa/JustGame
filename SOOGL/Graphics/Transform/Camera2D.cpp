#include "Camera2D.hpp"
#include <cmath>

namespace sgl
{
	const mat3& Camera2D::matrix() const
	{
		if (need_update)
		{
			mat3::createCameraMatrix(t, m_matrix);
			need_update = false;
		}

		return m_matrix;
	}
	const Camera2D Camera2D::by_default;
}