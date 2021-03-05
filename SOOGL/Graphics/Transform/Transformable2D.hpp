#pragma once

#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/mat3.hpp"

namespace sgl
{
	struct Transform2D
	{
		fvec2 position;
		float rotation;
		fvec2 scale;

		Transform2D();
	};

	class Transformable2D
	{
	protected:
		Transform2D t;

		mutable mat3 m_matrix;
		mutable bool need_update = true;
	public:
		Transformable2D() = default;
		virtual ~Transformable2D() = default;

		inline const Transform2D& transform() const {
			return t;
		}
		
		inline const fvec2& position() const {
			return t.position;
		}
		inline float rotation() const {
			return t.rotation;
		}
		inline const fvec2& scope() const {
			return t.scale;
		}

		const fvec2& position(float new_x, float new_y);
		const fvec2& position(const fvec2& new_pos);
		const fvec2& move(float offset_x, float offset_y);
		const fvec2& move(const fvec2& offset);

		float rotation(float rotation);
		float rotate(float rot);

		const fvec2& scope(float new_x, float new_y);
		const fvec2& scope(const fvec2& new_scale);
		const fvec2& zoom(float offset_x, float offset_y);
		const fvec2& zoom(const fvec2& scale);
		const fvec2& zoom(float offset);

		virtual const mat3& matrix() const;
	};
}