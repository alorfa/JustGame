#include "Camera2D.hpp"
#include <cmath>

namespace sgl
{
	const mat3& Camera2D::matrix() const
	{
		if (need_update)
		{
			// Projection components
			float a = 2.f / t.scale.x;
			float b = 2.f / t.scale.y;

			float cosine = std::cosf(t.rotation);
			float sine = std::sinf(t.rotation);
			float tx = t.position.x;
			float ty = t.position.y;

			m_matrix.set(
				a * cosine,		-b * sine,		0.f,
				a * sine,		b * cosine,		0.f,
				-a * tx,		-b * ty,		1.f);
		}
		need_update = false;

		return m_matrix;
	}
	const Camera2D Camera2D::by_default;
}