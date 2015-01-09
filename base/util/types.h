#pragma once

// these types don't exist on win
/*typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
typedef __int64 int64_t;
typedef __int32 int32_t;
typedef __int16 int16_t;
typedef __int8 int8_t;*/

// THANKS: From here: http://fastcpp.blogspot.dk/2011/03/changing-sign-of-float-values-using-sse.html
static const __m128 kSignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));


// THANKS: Operator overloading inspired by ryg: https://github.com/rygorous/intel_occlusion_cull/blob/blog/SoftwareOcclusionCulling/HelperSSE.h
union vec4f_t
{
	float f[4];
	__m128 v;

	vec4f_t() {}
	explicit vec4f_t(const float x) : v(_mm_set1_ps(x)) {}
	vec4f_t(const __m128& in) : v(in) {}
	vec4f_t(const vec4f_t& x) : v(x.v) {}
	vec4f_t(float x1, float x2, float x3, float x4) : v(_mm_setr_ps(x1, x2, x3, x4)) {} // We use setr because the values are stored little-endian, the reverse of what you'd expect.

	static vec4f_t zero()                    { return vec4f_t(_mm_setzero_ps()); }
	static vec4f_t load(const float* ptr)   { return vec4f_t(_mm_load_ps(ptr)); }
	static vec4f_t loadu(const float* ptr)  { return vec4f_t(_mm_loadu_ps(ptr)); }
	void store(float* ptr)                   { _mm_store_ps(ptr, v); }
	void storeu(float* ptr)                  { _mm_storeu_ps(ptr, v); }

	vec4f_t& operator=(const vec4f_t& other) { v = other.v; return *this; }
	vec4f_t& operator+=(const vec4f_t& other) { v = _mm_add_ps(v, other.v); return *this; }
	vec4f_t& operator-=(const vec4f_t& other) { v = _mm_sub_ps(v, other.v); return *this; }
	vec4f_t& operator*=(const vec4f_t& other) { v = _mm_mul_ps(v, other.v); return *this; }
	vec4f_t& operator/=(const vec4f_t& other) { v = _mm_div_ps(v, other.v); return *this; }

	vec4f_t operator-() const // unary minus
	{
		return vec4f_t(_mm_xor_ps(v, kSignMask));
	}

	operator __m128() const {
		return v;
	}

};

inline vec4f_t operator+(const vec4f_t& a, const vec4f_t& b) { return vec4f_t(_mm_add_ps(a.v, b.v)); }
inline vec4f_t operator-(const vec4f_t& a, const vec4f_t& b) { return vec4f_t(_mm_sub_ps(a.v, b.v)); }
inline vec4f_t operator*(const vec4f_t& a, const vec4f_t& b) { return vec4f_t(_mm_mul_ps(a.v, b.v)); }
inline vec4f_t operator/(const vec4f_t& a, const vec4f_t& b) { return vec4f_t(_mm_div_ps(a.v, b.v)); }

inline vec4f_t cross(const vec4f_t& a, const vec4f_t& b)
{
	// THANKS: From this page: http://fastcpp.blogspot.dk/2011/04/vector-cross-product-using-sse-code.html
	return vec4f_t(_mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(a.v, a.v, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(b.v, b.v, _MM_SHUFFLE(3, 1, 0, 2))), 
		_mm_mul_ps(_mm_shuffle_ps(a.v, a.v, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(b.v, b.v, _MM_SHUFFLE(3, 0, 2, 1)))
	));
}

inline float dot(const vec4f_t& a, const vec4f_t& b)
{
	__m128 s;
	__declspec( align( 16 ) ) float res;

	s = _mm_mul_ps(a.v, b.v);
	s = _mm_hadd_ps(s, s);
	s = _mm_hadd_ps(s, s);
	_mm_store_ss(&res, s);

	return res;
}

inline float length(const vec4f_t& a)
{
	__m128 s;
	__declspec( align( 16 ) ) float res;

	s = _mm_mul_ps(a.v, a.v);
	s = _mm_hadd_ps(s, s);
	s = _mm_hadd_ps(s, s);
	s = _mm_sqrt_ss(s);
	_mm_store_ss(&res, s);

	return res;
}

inline vec4f_t normalize(const vec4f_t& a)
{
	__m128 dp, inversenorm;

	dp = _mm_mul_ps(a.v, a.v);
	dp = _mm_hadd_ps(dp, dp);
	dp = _mm_hadd_ps(dp, dp);

	inversenorm = _mm_rsqrt_ps(dp);

	return vec4f_t(a*vec4f_t(inversenorm));
}

// function sqrt: square root
static inline vec4f_t sqrt(vec4f_t const & a) {
    return _mm_sqrt_ps(a);
}

// This from Agner Fog
#define INSTRSET 3
// Horizontal add: Calculates the sum of all vector elements.
static inline float horizontal_add (vec4f_t const & a) {
#if  INSTRSET >= 3  // SSE3
    __m128 t1 = _mm_hadd_ps(a,a);
    __m128 t2 = _mm_hadd_ps(t1,t1);
    return _mm_cvtss_f32(t2);        
#else
    __m128 t1 = _mm_movehl_ps(a,a);
    __m128 t2 = _mm_add_ps(a,t1);
    __m128 t3 = _mm_shuffle_ps(t2,t2,1);
    __m128 t4 = _mm_add_ss(t2,t3);
    return _mm_cvtss_f32(t4);
#endif
}

// Generate a constant vector of 4 integers stored in memory.
// Can be converted to any integer vector type
template <int i0, int i1, int i2, int i3>
static inline __m128i constant4i() {
    static const union {
        int     i[4];
        __m128i xmm;
    } u = {{i3,i2,i1,i0}};
    return u.xmm;
}

// NOTE> THE ABOVE MAY OR MAY NOT BE ENDIAN REVERSE


/*****************************************************************************
*
*          Vector Vec4f permute and blend functions
*
******************************************************************************
*
* The permute function can reorder the elements of a vector and optionally
* set some elements to zero. 
*
* The indexes are inserted as template parameters in <>. These indexes must be
* constants. Each template parameter is an index to the element you want to 
* select. A negative index will generate zero.
*
* Example:
* Vec4f a(10.f,11.f,12.f,13.f);        // a is (10,11,12,13)
* Vec4f b, c;
* b = permute4f<0,0,2,2>(a);           // b is (10,10,12,12)
* c = permute4f<3,2,-1,-1>(a);         // c is (13,12, 0, 0)
*
*
* The blend function can mix elements from two different vectors and
* optionally set some elements to zero. 
*
* The indexes are inserted as template parameters in <>. These indexes must be
* constants. Each template parameter is an index to the element you want to 
* select, where indexes 0 - 3 indicate an element from the first source
* vector and indexes 4 - 7 indicate an element from the second source vector.
* A negative index will generate zero.
*
*
* Example:
* Vec4f a(10.f,11.f,12.f,13.f);        // a is (10, 11, 12, 13)
* Vec4f b(20.f,21.f,22.f,23.f);        // b is (20, 21, 22, 23)
* Vec4f c;
* c = blend4f<1,4,-1,7> (a,b);         // c is (11, 20,  0, 23)
*
* Don't worry about the complicated code for these functions. Most of the
* code is resolved at compile time to generate only a few instructions.
*****************************************************************************/

#pragma warning ( push )
#pragma warning ( disable: 4127 )

// permute vector vec4f_t
template <int i0, int i1, int i2, int i3>
static inline vec4f_t permute4f(vec4f_t const & a) {
    // is shuffling needed
    const bool do_shuffle = (i0 > 0) || (i1 != 1 && i1 >= 0) || (i2 != 2 && i2 >= 0) || (i3 != 3 && i3 >= 0);
    // is zeroing needed
    const bool do_zero    = (i0 | i1 | i2 | i3) < 0 && ((i0 | i1 | i2 | i3) & 0x80);

    if (!do_shuffle && !do_zero) {
        return a;                                          // trivial case: do nothing
    }
    if (do_zero && !do_shuffle) {                          // zeroing, not shuffling
        if ((i0 & i1 & i2 & i3) < 0) return _mm_setzero_ps(); // zero everything
        // zero some elements
        __m128i mask1 = constant4i< -int(i0>=0), -int(i1>=0), -int(i2>=0), -int(i3>=0) >();
        return  _mm_and_ps(a,_mm_castsi128_ps(mask1));     // zero with AND mask
    }
    if (do_shuffle && !do_zero) {                          // shuffling, not zeroing        
        return _mm_shuffle_ps(a, a, (i0&3) | (i1&3)<<2 | (i2&3)<<4 | (i3&3)<<6);
    }
    // both shuffle and zero
    if ((i0 & i1) < 0 && (i2 | i3) >= 0) {                 // zero low half, shuffle high half
        return _mm_shuffle_ps(_mm_setzero_ps(), a, (i2&3)<<4 | (i3&3)<<6);
    }
    if ((i0 | i1) >= 0 && (i2 & i3) < 0) {                 // shuffle low half, zero high half
        return _mm_shuffle_ps(a, _mm_setzero_ps(), (i0&3) | (i1&3)<<2);
    }
#if  INSTRSET >= 4  // SSSE3
    // With SSSE3 we can do both with the PSHUFB instruction
    const int j0 = (i0 & 3) << 2;
    const int j1 = (i1 & 3) << 2;
    const int j2 = (i2 & 3) << 2;
    const int j3 = (i3 & 3) << 2;
    __m128i mask2 = constant4i <
        i0 < 0 ? -1 : j0 | (j0+1)<<8 | (j0+2)<<16 | (j0+3) << 24,
        i1 < 0 ? -1 : j1 | (j1+1)<<8 | (j1+2)<<16 | (j1+3) << 24,
        i2 < 0 ? -1 : j2 | (j2+1)<<8 | (j2+2)<<16 | (j2+3) << 24,
        i3 < 0 ? -1 : j3 | (j3+1)<<8 | (j3+2)<<16 | (j3+3) << 24 > ();
    return _mm_castsi128_ps(_mm_shuffle_epi8(_mm_castps_si128(a),mask2));
#else
    __m128 t1 = _mm_shuffle_ps(a, a, (i0&3) | (i1&3)<<2 | (i2&3)<<4 | (i3&3)<<6); // shuffle
    __m128i mask3 = constant4i< -int(i0>=0), -int(i1>=0), -int(i2>=0), -int(i3>=0) >();
    return _mm_and_ps(t1,_mm_castsi128_ps(mask3));     // zero with AND mask
#endif
}


// blend vectors vec4f_t
template <int i0, int i1, int i2, int i3>
static inline vec4f_t blend4f(vec4f_t const & a, vec4f_t const & b) {

    // Combine all the indexes into a single bitfield, with 8 bits for each
    const int m1 = (i0&7) | (i1&7)<<8 | (i2&7)<<16 | (i3&7)<<24; 

    // Mask to zero out negative indexes
    const int m2 = (i0<0?0:0xFF) | (i1<0?0:0xFF)<<8 | (i2<0?0:0xFF)<<16 | (i3<0?0:0xFF)<<24;

    if ((m1 & 0x04040404 & m2) == 0) {
        // no elements from b
        return permute4f<i0,i1,i2,i3>(a);
    }
    if (((m1^0x04040404) & 0x04040404 & m2) == 0) {
        // no elements from a
        return permute4f<i0&~4, i1&~4, i2&~4, i3&~4>(b);
    }
    if (((m1 & ~0x04040404) ^ 0x03020100) == 0 && m2 == -1) {
        // selecting without shuffling or zeroing
        __m128i sel = constant4i <i0 & 4 ? 0 : -1, i1 & 4 ? 0 : -1, i2 & 4 ? 0 : -1, i3 & 4 ? 0 : -1> ();
        return selectf(_mm_castsi128_ps(sel), a, b);
    }
#ifdef __XOP__     // Use AMD XOP instruction PPERM
    __m128i maska = constant4i <
        i0 < 0 ? 0x80808080 : (i0*4 & 31) + (((i0*4 & 31) + 1) << 8) + (((i0*4 & 31) + 2) << 16) + (((i0*4 & 31) + 3) << 24),
        i1 < 0 ? 0x80808080 : (i1*4 & 31) + (((i1*4 & 31) + 1) << 8) + (((i1*4 & 31) + 2) << 16) + (((i1*4 & 31) + 3) << 24),
        i2 < 0 ? 0x80808080 : (i2*4 & 31) + (((i2*4 & 31) + 1) << 8) + (((i2*4 & 31) + 2) << 16) + (((i2*4 & 31) + 3) << 24),
        i3 < 0 ? 0x80808080 : (i3*4 & 31) + (((i3*4 & 31) + 1) << 8) + (((i3*4 & 31) + 2) << 16) + (((i3*4 & 31) + 3) << 24) > ();
    return _mm_castsi128_ps(_mm_perm_epi8(_mm_castps_si128(a), _mm_castps_si128(b), maska));
#else
    if ((((m1 & ~0x04040404) ^ 0x03020100) & m2) == 0) {
        // selecting and zeroing, not shuffling
        __m128i sel1  = constant4i <i0 & 4 ? 0 : -1, i1 & 4 ? 0 : -1, i2 & 4 ? 0 : -1, i3 & 4 ? 0 : -1> ();
        __m128i mask1 = constant4i< -int(i0>=0), -int(i1>=0), -int(i2>=0), -int(i3>=0) >();
        __m128 t1 = selectf(_mm_castsi128_ps(sel1), a, b);   // select
        return  _mm_and_ps(t1, _mm_castsi128_ps(mask1));     // zero
    }
    // general case. combine two permutes
    __m128 a1 = permute4f <
        (uint32_t)i0 < 4 ? i0 : -1,
        (uint32_t)i1 < 4 ? i1 : -1,
        (uint32_t)i2 < 4 ? i2 : -1,
        (uint32_t)i3 < 4 ? i3 : -1  > (a);
    __m128 b1 = permute4f <
        (uint32_t)(i0^4) < 4 ? (i0^4) : -1,
        (uint32_t)(i1^4) < 4 ? (i1^4) : -1,
        (uint32_t)(i2^4) < 4 ? (i2^4) : -1,
        (uint32_t)(i3^4) < 4 ? (i3^4) : -1  > (b);
    return  _mm_or_ps(a1,b1);
#endif // __XOP__
}

// change signs on vectors vec4f_t
// Each index i0 - i3 is 1 for changing sign on the corresponding element, 0 for no change
template <int i0, int i1, int i2, int i3>
static inline vec4f_t change_sign(vec4f_t const & a) {
    if ((i0 | i1 | i2 | i3) == 0) return a;
    __m128i mask = constant4i<i0 ? 0x80000000 : 0, i1 ? 0x80000000 : 0, i2 ? 0x80000000 : 0, i3 ? 0x80000000 : 0>();
    return  _mm_xor_ps(a, _mm_castsi128_ps(mask));     // flip sign bits
}

#pragma warning(pop)
