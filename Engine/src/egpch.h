#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


#include "Log.h"

#ifdef EG_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // #EG_PLATFORM_WINDOWS