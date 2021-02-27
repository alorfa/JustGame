#pragma once

#include "SOOGL/Other/types.hpp"

namespace sgl
{
namespace vec
{
	template <typename T>
	struct vec3
	{
		T x, y, z;

		vec3(T x = 0, T y = 0, T z = 0)
			: x(x), y(y), z(z) {}
	};

#define SOOGL_OPERATOR_IMPL(oper)											\
	template <typename type>												\
	vec3<type> operator oper(vec3<type> v1, vec3<type> v2)					\
	{																		\
		return vec3<type>(													\
			v1.x oper v2.x, v1.y oper v2.y, v1.z oper v2.z);				\
	}																		\
	template <typename type>												\
	vec3<type> operator oper(vec3<type> v1, type value)						\
	{																		\
		return vec3<type>(													\
			v1.x oper value, v1.y oper value, v1.z oper value);				\
	}																		\
	template <typename type>												\
	vec3<type>& operator oper##=(vec3<type>& v1, vec3<type> v2)				\
	{																		\
		v1.x oper##= v2.x;													\
		v1.y oper##= v2.y;													\
		v1.z oper##= v2.z;													\
		return v1;															\
	}																		\
	template <typename type>												\
	vec3<type>& operator oper##=(vec3<type>& v1,type value)					\
	{																		\
		v1.x oper##= value;													\
		v1.y oper##= value;													\
		v1.z oper##= value;													\
		return v1;															\
	}

	SOOGL_OPERATOR_IMPL(+);
	SOOGL_OPERATOR_IMPL(-);
	SOOGL_OPERATOR_IMPL(*);
	SOOGL_OPERATOR_IMPL(/ );

#undef SOOGL_OPERATOR_IMPL

	using fvec3 = vec3<float>;
	using dvec3 = vec3<double>;

	using ivec3 = vec3<types::int32>;
	using uivec3 = vec3<types::uint32>;
	using uvec3 = uivec3;

	using ubvec3 = vec3<types::ubyte>;
	using sbvec3 = vec3<types::sbyte>;

	using vec3_size = vec3<size_t>;
}
using namespace vec;
}