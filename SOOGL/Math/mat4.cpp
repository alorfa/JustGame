#include "SOOGL/Math/mat4.hpp"
#include <cstdlib>
#include <iostream>

namespace sgl
{
	mat4::mat4(const float* mat) noexcept
	{
		memcpy(this->mat, mat, sizeof(mat4));
	}
	mat4::mat4(const mat4& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat4));
	}
	mat4::mat4(mat4&& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat4));
	}

	mat4& mat4::operator=(const mat4& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat4));
		return *this;
	}

	mat4& mat4::operator=(mat4&& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat4));
		return *this;
	}

	void mat4::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		mat[0] = m11;
		mat[1] = m12;
		mat[2] = m13;
		mat[3] = m14;
		mat[4] = m21;
		mat[5] = m22;
		mat[6] = m23;
		mat[7] = m24;
		mat[8] = m31;
		mat[9] = m32;
		mat[10] = m33;
		mat[11] = m34;
		mat[12] = m41;
		mat[13] = m42;
		mat[14] = m43;
		mat[15] = m44;
	}

	mat4::mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
	{
		mat[0] = m11;
		mat[1] = m12;
		mat[2] = m13;
		mat[3] = m14;
		mat[4] = m21;
		mat[5] = m22;
		mat[6] = m23;
		mat[7] = m24;
		mat[8] = m31;
		mat[9] = m32;
		mat[10] = m33;
		mat[11] = m34;
		mat[12] = m41;
		mat[13] = m42;
		mat[14] = m43;
		mat[15] = m44;
	}
	const mat4 mat4::identity(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);

	void mat4::multiply(const mat4& m1_m, const mat4& m2_m, mat4& output_m)
	{
		float* output = output_m.mat;
		const float* m1 = m1_m.mat;
		const float* m2 = m2_m.mat;

		output[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
		output[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
		output[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
		output[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

		output[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
		output[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
		output[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
		output[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

		output[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
		output[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
		output[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
		output[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

		output[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
		output[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
		output[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
		output[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
	}
}