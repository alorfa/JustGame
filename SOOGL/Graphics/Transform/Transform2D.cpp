#include "Transform2D.hpp"
#include "SOOGL/Math/trig.hpp"
#include <cmath>

namespace sgl
{
	Transform2D::Transform2D()
		: position(), rotation(0), scale(1.f, 1.f) {}

	const fvec2& Transformable2D::position(float new_x, float new_y)
	{
		need_update = true;
		t.position.x = new_x;
		t.position.y = new_y;
		return t.position;
	}
	const fvec2& Transformable2D::position(const fvec2& new_pos)
	{
		return position(new_pos.x, new_pos.y);
	}
	float Transformable2D::rotation(float rotation)
	{
		need_update = true;
		return t.rotation = rotation;
	}
	const fvec2& Transformable2D::scope(float new_x, float new_y)
	{
		need_update = true;
		t.scale.x = new_x;
		t.scale.y = new_y;
		return t.scale;
	}
	const fvec2& Transformable2D::scope(const fvec2& new_scale)
	{
		return scope(new_scale.x, new_scale.y);
	}

	const fvec2& Transformable2D::move(float offset_x, float offset_y)
	{
		return position(t.position.x + offset_x, t.position.y + offset_y);
	}

	const fvec2& Transformable2D::move(const fvec2& offset)
	{
		return move(offset.x, offset.y);
	}

	float Transformable2D::rotate(float radians)
	{
		return rotation(t.rotation + radians);
	}

	const fvec2& Transformable2D::zoom(float new_x, float new_y)
	{
		return scope(t.scale.x * new_x, t.scale.y * new_y);
	}

	const fvec2& Transformable2D::zoom(const fvec2& scale)
	{
		return this->zoom(scale.x, scale.y);
	}

	const fvec2& Transformable2D::zoom(float offset)
	{
		return zoom(offset, offset);
	}

	const mat3& Transformable2D::matrix() const
	{
		if (need_update)
		{
			float cosine = std::cosf(t.rotation);
			float sine = std::sinf(t.rotation);
			float scalxc = t.scale.x * cosine;
			float scalyc = t.scale.y * cosine;
			float scalxs = t.scale.x * sine;
			float scalys = t.scale.y * sine;
			float tx = t.position.x;
			float ty = t.position.y;

			m_matrix.set(
				scalxc,		-scalxs,	0.f,
				scalys,		scalyc,		0.f,
				tx,			ty,			1.f);
		}
		need_update = false;

		return m_matrix;
	}


}