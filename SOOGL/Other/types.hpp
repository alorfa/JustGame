#pragma once

namespace sgl
{
	using int8 = __int8;
	using int16 = __int16;
	using int32 = __int32;
	using int64 = __int64;

	using uint8 = unsigned __int8;
	using uint16 = unsigned __int16;
	using uint32 = unsigned __int32;
	using uint64 = unsigned __int64;

	using uint = uint32;
	using ulong = uint64;

	using sbyte = int8;
	using ubyte = uint8;

	namespace types
	{
		using namespace sgl;
	}
	namespace primitives
	{
		using namespace sgl;
	}
}