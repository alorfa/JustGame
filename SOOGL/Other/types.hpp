#pragma once

#include <stdint.h>

namespace sgl
{
	using int8 = int8_t;
	using int16 = int16_t;
	using int32 = int32_t;
	using int64 = int64_t;

	using uint8 = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	using uint = uint32;
	using ulong = uint64;

	using sbyte = int8;
	using ubyte = uint8;

	namespace types
	{
		using sgl::int8;
		using sgl::int16;
		using sgl::int32;
		using sgl::int64;

		using sgl::uint8;
		using sgl::uint16;
		using sgl::uint32;
		using sgl::uint64;

		using sgl::uint;
		using sgl::ulong;

		using sgl::sbyte;
		using sgl::ubyte;
	}
	namespace primitives
	{
		using namespace types;
	}
}