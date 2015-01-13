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

#include "config.h" // this file controls ZENABLE* defines. Including project must ensure that such a file exists in path.

#include "base/util/inline.h"
#include "base/util/alloc.h"
#include "base/util/align.h"
#include "base/util/types.h"
#include "base/util/new.h"
#include "base/util/fpustate.h"

#include "base/math/mathdefines.h"
#include "base/math/math.h"
#include "base/math/random.h"
#include "base/util/mem.h"
#include "base/util/str.h"
#include "base/util/error.h"
#include "base/util/thread.h"

#include "base/util/debug.h"
#include "base/util/mutex.h"
#include "base/math/random.h"
#include "base/util/time.h"

#include "base/util/assert.h"
#include "base/util/registry.h"

#include "base/util/smartptr.h"

#include "base/datatypes/hash.h"
#include "base/datatypes/stack.h"
#include "base/datatypes/vector.h"
#include "base/datatypes/list.h"
#include "base/datatypes/hashmap.h"