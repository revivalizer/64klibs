#ifdef __GNUC__
	#define ZINLINE inline
	#define ZFORCEINLINE inline __attribute__((always_inline))
#elif _MSC_VER
	#define ZINLINE inline
	#define ZFORCEINLINE __forceinline 
#else
	#error Unknown compiler.
#endif