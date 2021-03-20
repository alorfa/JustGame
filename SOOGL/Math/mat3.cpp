#include "SOOGL/Math/mat3.hpp"
#include <iostream>
#include "SOOGL/Graphics/Transform/Camera2DBase.hpp"

namespace sgl
{
	mat3::mat3(const float* mat) noexcept
	{
		memcpy(this->mat, mat, sizeof(mat3));
	}
	mat3::mat3(const mat3& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat3));
	}
	mat3::mat3(mat3&& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat3));
	}

	mat3& mat3::operator=(const mat3& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat3));
		return *this;
	}

	mat3& mat3::operator=(mat3&& mat) noexcept
	{
		memcpy(this->mat, mat.mat, sizeof(mat3));
		return *this;
	}

	void mat3::set(float m11, float m12, float m13, float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		mat[0] = m11;
		mat[1] = m12;
		mat[2] = m13;
		mat[3] = m21;
		mat[4] = m22;
		mat[5] = m23;
		mat[6] = m31;
		mat[7] = m32;
		mat[8] = m33;
	}

	mat3::mat3(float m11, float m12, float m13, float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		mat[0] = m11;
		mat[1] = m12;
		mat[2] = m13;
		mat[3] = m21;
		mat[4] = m22;
		mat[5] = m23;
		mat[6] = m31;
		mat[7] = m32;
		mat[8] = m33;
	}
	const mat3 mat3::identity(
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
	);

	void mat3::multiply(const mat3& m1_m, const mat3& m2_m, mat3& output_m)
	{
		float* output = output_m.mat;
		const float* m1 = m1_m.mat;
		const float* m2 = m2_m.mat;

		output[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
		output[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
		output[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];

		output[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
		output[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
		output[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];

		output[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
		output[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
		output[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];
	}
	void mat3::multiply(const mat3& m, const vec::fvec3 v, vec::fvec3& output)
	{
		output.x = m[0] * v.x + m[3] * v.y + m[6] * v.z;
		output.y = m[1] * v.x + m[4] * v.y + m[7] * v.z;
		output.z = m[2] * v.x + m[5] * v.y + m[8] * v.z;
	}
	void mat3::createTransformMatrix(const Transform2D& t, mat3& output)
	{
		float cosine = std::cosf(t.rotation);
		float sine = std::sinf(t.rotation);
		float scalxc = t.scale.x * cosine;
		float scalyc = t.scale.y * cosine;
		float scalxs = t.scale.x * sine;
		float scalys = t.scale.y * sine;
		float tx = t.position.x;
		float ty = t.position.y;

		output.set(
			scalxc, -scalxs, 0.f,
			scalys, scalyc, 0.f,
			tx, ty, 1.f);
	}
	void mat3::createCameraMatrix(const Transform2D& t, mat3& output)
	{
		// Projection components
		float a = 2.f / t.scale.x;
		float b = 2.f / t.scale.y;

		float cosine = std::cosf(t.rotation);
		float sine = std::sinf(t.rotation);
		float tx = t.position.x;
		float ty = t.position.y;

		output.set(
			a * cosine, -b * sine,	0.f,
			a * sine,	b * cosine, 0.f,
			-a * tx,	-b * ty,	1.f);
	}
	void mat3::createMatrix(const Transform2D& camera, 
		const Transform2D& object, mat3& output)
	{
		Transform2D t;

		t.scale.x = object.scale.x * 2.f / camera.scale.x;
		t.scale.y = object.scale.y * 2.f / camera.scale.y;

		t.position.x = (object.position.x - camera.position.x) * 2.f;
		t.position.y = (object.position.y - camera.position.y) * 2.f;

		t.rotation = object.rotation - camera.rotation;

		mat3::createTransformMatrix(t, output);
	}
	void mat3::createMatrix(const Camera2DBase& camera, 
		const Transformable2D& object, mat3& output)
	{
		createMatrix(camera.transform(), object.transform(), output);
	}
}