#pragma once

#include <ostream>
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/vec3.hpp"
#include "SOOGL/Math/vec4.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& out, const sgl::vec2<T>& vec)
{
	out << '[' << vec.x << ", " << vec.y << "]";
	return out;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const sgl::vec3<T>& vec)
{
	out << '[' << vec.x << ", " << vec.y << ", " << vec.z << "]";
	return out;
}
template <typename T>
std::ostream& operator<<(std::ostream& out, const sgl::vec4<T>& vec)
{
	out << '[' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
	return out;
}