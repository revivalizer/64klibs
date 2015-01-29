#pragma once

#ifdef ENABLE_ZASSERT
	#pragma warning(push)
	#pragma warning(disable: 4793)
	#pragma warning(disable : 4800)

	#ifndef ZASSERT
		#define ZASSERT(exp) if( !static_cast<bool>(exp) ) { _asm{ int 3 } }
	#endif

	#ifndef ZBREAK
		#define ZBREAK() { _asm{ int 3 } }
	#endif

	#pragma warning(pop)
#else
	#ifndef ZASSERT
		#define ZASSERT(exp)
	#endif
	#ifndef ZBREAK
		#define ZBREAK()
	#endif
#endif