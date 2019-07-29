#pragma once

#ifdef EG_PLATFORM_WINDOWS
	#define DEBUG_BREAK __debugbreak()
#else
	#define DEBUG_BREAK __builtin_trap()
#endif

#ifdef EG_DEBUG
	#define EG_ENABLE_ASSERTS
#else
	#warning "---Not Debug---"
	
#endif

#ifdef EG_ENABLE_ASSERTS
	#define EG_ASSERT(x, ...) { if(!(x)) { EG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; } }	
	#define EG_CORE_ASSERT(x, ...) { if(!(x)) { EG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; } }
#else	
	#define EG_ASSERT(x, ...)
	#define EG_CORE_ASSERT(x, ...)
#endif

#define EG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 
#define BIT(x) (1 << x)

/*
How a bitfield works.

#define KEY_RIGHT  (1 << 0) // 00000001 
#define KEY_LEFT   (1 << 1) // 00000010 
#define KEY_DOWN   (1 << 2) // 00000100 
#define KEY_UP     (1 << 3) // 00001000 
#define KEY_START  (1 << 4) // 00010000 
#define KEY_SELECT (1 << 5) // 00100000 
#define KEY_B      (1 << 6) // 01000000 
#define KEY_A      (1 << 7) // 10000000 
*/