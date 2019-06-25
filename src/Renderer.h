#pragma once
#include <GL/glew.h>

#ifdef _MSC_VER
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK __builtin_trap()
#endif

#define ASSERT(x) if (!(x)) DEBUG_BREAK;
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GlLogCall(const char* function, const char* file, int line);