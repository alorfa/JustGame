#pragma once

#include "SOOGL/Math/mat3.hpp"
#include "SOOGL/Math/mat4.hpp"
#include <iostream>

using namespace sgl::mat;

std::ostream& operator<<(std::ostream& out, const mat4& mat);
std::ostream& operator<<(std::ostream& out, const mat3& mat);

namespace sgl::tests
{
	inline void matrixes_test()
	{
		using namespace std;

		float mat_content[9] = {
			1.f, 0.f, 1.f,
			0.f, 1.f, 1.f,
			0.f, 0.f, 1.f
		};
		mat3 m1(mat_content);
		cout << m1 << endl << endl;
		m1.set(
			1.f, 0.f, 1.f,
			0.f, 1.f, 1.f,
			0.f, 0.f, 1.f
		);
		cout << m1 << endl;
	}
}