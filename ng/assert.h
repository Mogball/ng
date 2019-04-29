#pragma once

#include <cassert>

#ifndef NG_RELEASE
#define ng_assert(cond) assert(cond)
#else
#define ng_assert(...)
#endif
