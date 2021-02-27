#pragma once

#include "SOOGL/Other/types.hpp"

namespace sgl
{
namespace vec
{
	template <typename T>
	struct vec2
	{
		T x, y;

		vec2(T x = 0, T y = 0)
			: x(x), y(y) {}
	};

#define SOOGL_VECTOR_OPERATOR_IMPL(oper)									\
	template <typename type>												\
	vec2<type> operator oper(vec2<type> v1, vec2<type> v2)					\
	{																		\
		return vec2<type>(v1.x oper v2.x, v1.y oper v2.y);					\
	}																		\
	template <typename type>												\
	vec2<type>& operator oper##=(vec2<type>& v1, vec2<type> v2)				\
	{																		\
		v1.x oper##= v2.x;													\
		v1.y oper##= v2.y;													\
		return v1;															\
	}

#define SOOGL_SCALAR_OPERATOR_IMPL(oper)									\
	template <typename type>												\
	vec2<type> operator oper(vec2<type> v1, type value)						\
	{																		\
		return vec2<type>(v1.x oper value, v1.y oper value);				\
	}																		\
	template <typename type>												\
	vec2<type>& operator oper##=(vec2<type>& v1, type value)				\
	{																		\
		v1.x oper##= value;													\
		v1.y oper##= value;													\
		return v1;															\
	}

	SOOGL_VECTOR_OPERATOR_IMPL(+);
	SOOGL_VECTOR_OPERATOR_IMPL(-);
	SOOGL_VECTOR_OPERATOR_IMPL(*);
	SOOGL_VECTOR_OPERATOR_IMPL(/ );

	SOOGL_SCALAR_OPERATOR_IMPL(+);
	SOOGL_SCALAR_OPERATOR_IMPL(-);
	SOOGL_SCALAR_OPERATOR_IMPL(*);
	SOOGL_SCALAR_OPERATOR_IMPL(/ );

#undef SOOGL_OPERATOR_IMPL

	using fvec2 = vec2<float>;
	using dvec2 = vec2<double>;

	using ivec2 = vec2<types::int32>;
	using uivec2 = vec2<types::uint32>;
	using uvec2 = uivec2;

	using ubvec2 = vec2<types::ubyte>;
	using sbvec2 = vec2<types::sbyte>;

	using vec2_size = vec2<size_t>;
}
using namespace vec;
}