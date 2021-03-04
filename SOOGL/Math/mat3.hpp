#pragma once

#include "vec3.hpp"

namespace sgl
{
	struct mat3
	{
	public:
		float mat[9] = { 0.f };

		mat3() = default;
		mat3(const float* mat) noexcept;
		mat3(float m11, float m12, float m13, float m21, float m22, float m23,
			float m31, float m32, float m33);
		mat3(const mat3& mat) noexcept;
		mat3(mat3&& mat) noexcept;

		mat3& operator=(const mat3& mat) noexcept;
		mat3& operator=(mat3&& mat) noexcept;

		void set(float m11, float m12, float m13, float m21, float m22, float m23,
			float m31, float m32, float m33);

		inline float& operator[](int index) {
			return mat[index];
		}
		inline float operator[](int index) const {
			return mat[index];
		}

		static const mat3 identity;
		static void multiply(const mat3& m1, const mat3& m2, mat3& output);
		static void multiply(const mat3& m, const vec::fvec3 v, vec::fvec3& output);
	};
	using mat3x3 = mat3;

	namespace mat
	{
		using namespace sgl;
	}
	namespace primitives
	{
		using namespace sgl;
	}
}