#pragma once

#pragma warning(push)
#pragma warning(disable : 4668)
#define WIN32_LEAN_AND_MEAN 
#define VC_EXTRALEAN
#include <windows.h>
#include <stdint.h>
#pragma warning(pop)

#include "xmmintrin.h" // SSE 1
#include "emmintrin.h" // SSE 2
#include "tmmintrin.h" // SSE 3.1

#include "libs/base/util/inline.h"
#include "libs/base/util/alloc.h"
#include "libs/base/util/align.h"
#include "libs/base/util/types.h"
#include "libs/base/util/new.h"
#include "libs/base/util/fpustate.h"

#include "libs/base/math/mathdefines.h"
#include "libs/base/math/math.h"
#include "libs/base/math/random.h"
#include "libs/base/util/mem.h"
#include "libs/base/util/str.h"
#include "libs/base/util/error.h"
#include "libs/base/util/thread.h"

#include "libs/base/util/debug.h"
#include "libs/base/util/mutex.h"
#include "libs/base/math/random.h"
#include "libs/base/util/time.h"

#include "libs/base/util/assert.h"
#include "libs/base/util/registry.h"

#include "libs/base/util/smartptr.h"

#include "libs/base/datatypes/hash.h"
#include "libs/base/datatypes/stack.h"
#include "libs/base/datatypes/vector.h"
#include "libs/base/datatypes/list.h"
#include "libs/base/datatypes/hashmap.h"