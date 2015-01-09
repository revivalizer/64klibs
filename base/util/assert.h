#pragma once

#ifdef ENABLE_ZASSERTS
	#pragma warning(disable: 4793)
	#pragma warning(disable : 4800)

	#ifndef ZASSERT
		#define ZASSERT(exp) if( !static_cast<bool>(exp) ) { _asm{ int 3 } }
	#endif

	#pragma warning(default: 4793)
	#pragma warning(default: 4800)
#else
	#ifndef ZASSERT
		#define ZASSERT(exp)
	#endif
#endif