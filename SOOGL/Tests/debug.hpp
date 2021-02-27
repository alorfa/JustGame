#pragma once

#include "SOOGL/Other/opengl.h"

#define SOOGL_DEBUG

inline bool& error_in_alf_test()
{
	static bool val = false;
	return val;
}

#ifdef SOOGL_DEBUG

#include <iostream>

#define PRINT(x) std::cout << #x " = " << (x) << std::endl
#define PRINTR(x) std::cout << "\r" #x " = " << (x) << "                "

#define REPORT_IF_FALSE(a1, a2) \
if (a1 != a2) {											\
	std::cout << #a1 " != " #a2 "" << std::endl;		\
	std::cout << (a1) << " != " << (a2) << std::endl;	\
	error_in_alf_test = true;							\
}

inline void clear_test()
{
	error_in_alf_test() = false;
}

inline void print_if_success(const std::string& string)
{
	if (not error_in_alf_test())
		std::cout << string << std::endl;
}
inline void print_if_failed(const std::string& string)
{
	if (error_in_alf_test())
		std::cout << string << std::endl;
}
inline int& OGL_ERR_COUNT() 
{
	static int count = 0;
	return count;
}
inline bool OGL_ERROR()
{
	auto oglError = glGetError();
	if (oglError)
	{
		PRINT(oglError);
		OGL_ERR_COUNT()++;
		return true;
	}
	return false;
}

#else

#define PRINT(x)
#define PRINTR(x)

#define REPORT_IF_FALSE(a1, a2)

inline void clear_test() {}

inline void print_if_success(const std::string& string) {}
inline void print_if_failed(const std::string& string) {}

inline bool OGL_ERROR() {}

#endif //SOOGL_DEBUG