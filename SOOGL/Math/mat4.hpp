#pragma once

namespace sgl
{
namespace mat
{
	struct mat4
	{
	public:
		float mat[16] = { 0.f };

		mat4() = default;
		mat4(const float* mat) noexcept;
		mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
		mat4(const mat4& mat) noexcept;
		mat4(mat4&& mat) noexcept;

		mat4& operator=(const mat4& mat) noexcept;
		mat4& operator=(mat4&& mat) noexcept;

		void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

		inline float& operator[](int index) {
			return mat[index];
		}
		inline float operator[](int index) const {
			return mat[index];
		}

		static const mat4 identity;
		static void multiply(const mat4& m1, const mat4& m2, mat4& output);
	};
	using mat4x4 = mat4;
}
using namespace mat;
}