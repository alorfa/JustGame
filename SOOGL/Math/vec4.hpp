#pragma once

#include "SOOGL/Other/types.hpp"

namespace sgl
{
namespace vec
{
	template <typename type>
	struct vec4
	{
		type x, y, z, w;

		vec4(type x = 0, type y = 0, type z = 0, type w = 1)
			: x(x), y(y), z(z), w(w) {}
	};

#define SOOGL_OPERATOR_IMPL(oper)											\
	template <typename type>												\
	vec4<type> operator oper(vec4<type> v1, vec4<type> v2)					\
	{																		\
		return vec4<type>(													\
			v1.x oper v2.x, v1.y oper v2.y,									\
			v1.z oper v2.z, v1.w oper v2.w);								\
	}																		\
	template <typename type>												\
	vec4<type> operator oper(vec4<type> v1, type value)						\
	{																		\
		return vec4<type>(													\
			v1.x oper value, v1.y oper value,								\
			v1.z oper value, v1.w oper value);								\
	}																		\
	template <typename type>												\
	vec4<type>& operator oper##=(vec4<type>& v1, vec4<type> v2)				\
	{																		\
		v1.x oper##= v2.x;													\
		v1.y oper##= v2.y;													\
		v1.z oper##= v2.z;													\
		v1.w oper##= v2.w;													\
		return v1;															\
	}																		\
	template <typename type>												\
	vec4<type>& operator oper##=(vec4<type>& v1, type value)				\
	{																		\
		v1.x oper##= value;													\
		v1.y oper##= value;													\
		v1.z oper##= value;													\
		v1.w oper##= value;													\
		return v1;															\
	}

	SOOGL_OPERATOR_IMPL(+);
	SOOGL_OPERATOR_IMPL(-);
	SOOGL_OPERATOR_IMPL(*);
	SOOGL_OPERATOR_IMPL(/ );

#undef SOOGL_OPERATOR_IMPL

	using fvec4 = vec4<float>;
	using dvec4 = vec4<double>;

	using ivec4 = vec4<types::int32>;
	using uivec4 = vec4<types::uint32>;
	using uvec4 = uivec4;

	using ubvec4 = vec4<types::ubyte>;
	using sbvec4 = vec4<types::sbyte>;
}
}