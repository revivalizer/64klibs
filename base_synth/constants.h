#pragma once

const uint32_t kBlockSize = 16;
//const uint32_t kNumInstruments = 16; // not sure this should be defined here. probably belongs in synth, no?
//const uint32_t kNumVoices = 16;

enum { kNumVoices = 16 };

enum OversamplingFactor
{
	kOversample1x = 1,
	kOversample2x = 2,
	kOversample4x = 4,
	kOversample8x = 8,
};

enum 
{
	kDefaultOversampling = kOversample2x,
};

const double kSampleRate = 44100*kDefaultOversampling;
const uint32_t kiSampleRate = 44100*kDefaultOversampling;


// THANKS: Operator overloading inspired by ryg: https://github.com/rygorous/intel_occlusion_cull/blob/blog/SoftwareOcclusionCulling/HelperSSE.h
union sample_t
{
	double d[2];
	__m128d v;

	sample_t() {}
	sample_t(const double x) : v(_mm_set1_pd(x)) {}
	sample_t(const __m128d& in) : v(in) {}
	sample_t(const sample_t& x) : v(x.v) {}
	sample_t(double x1, double x2) : v(_mm_set_pd(x1, x2)) {}

	static sample_t zero()                    { return sample_t(_mm_setzero_pd()); }
	static sample_t load(const double* ptr)   { return sample_t(_mm_load_pd(ptr)); }
	static sample_t loadu(const double* ptr)  { return sample_t(_mm_loadu_pd(ptr)); }
	void store(double* ptr)                   { _mm_store_pd(ptr, v); }
	void storeu(double* ptr)                  { _mm_storeu_pd(ptr, v); }

	sample_t& operator=(const sample_t& other) { v = other.v; return *this; }
	sample_t& operator+=(const sample_t& other) { v = _mm_add_pd(v, other.v); return *this; }
	sample_t& operator-=(const sample_t& other) { v = _mm_sub_pd(v, other.v); return *this; }
	sample_t& operator*=(const sample_t& other) { v = _mm_mul_pd(v, other.v); return *this; }
	sample_t& operator/=(const sample_t& other) { v = _mm_div_pd(v, other.v); return *this; }
};

inline sample_t operator+(const sample_t& a, const sample_t& b) { return sample_t(_mm_add_pd(a.v, b.v)); }
inline sample_t operator-(const sample_t& a, const sample_t& b) { return sample_t(_mm_sub_pd(a.v, b.v)); }
inline sample_t operator*(const sample_t& a, const sample_t& b) { return sample_t(_mm_mul_pd(a.v, b.v)); }
inline sample_t operator/(const sample_t& a, const sample_t& b) { return sample_t(_mm_div_pd(a.v, b.v)); }

inline sample_t operator< (const sample_t& a, const sample_t& b) { return sample_t(_mm_cmplt_pd(a.v, b.v)); }
inline sample_t operator<=(const sample_t& a, const sample_t& b) { return sample_t(_mm_cmple_pd(a.v, b.v)); }
inline sample_t operator> (const sample_t& a, const sample_t& b) { return sample_t(_mm_cmpgt_pd(a.v, b.v)); }
inline sample_t operator>=(const sample_t& a, const sample_t& b) { return sample_t(_mm_cmpge_pd(a.v, b.v)); }
inline sample_t operator==(const sample_t& a, const sample_t& b) { return sample_t(_mm_cmpeq_pd(a.v, b.v)); }
inline sample_t operator!=(const sample_t& a, const sample_t& b) { return sample_t(_mm_cmpneq_pd(a.v, b.v)); }

inline sample_t select(const sample_t& test, const sample_t& restrue, const sample_t& resfalse)
{
	__m128d t = _mm_and_pd(restrue.v, test.v);
	__m128d f = _mm_andnot_pd(test.v, resfalse.v);
	__m128d r = _mm_or_pd(t, f);
	return sample_t(r);
}

union complex_t;
inline complex_t operator*(const complex_t& a, const complex_t& b);

extern complex_t conjugate_pd;


union complex_t
{
	double d[2]; // these will be SWAPPED due to endianess
	__m128d v;

	complex_t() {}
	explicit complex_t(const double x) : v(_mm_set_pd(x, 0.0)) {} // convert double to real
	complex_t(const __m128d& in) : v(in) {}
	complex_t(const complex_t& x) : v(x.v) {}
	complex_t(double x1, double x2) : v(_mm_set_pd(x1, x2)) {}

	static complex_t zero()                    { return complex_t(_mm_setzero_pd()); }
	static complex_t load(const double* ptr)   { return complex_t(_mm_load_pd(ptr)); }
	static complex_t loadu(const double* ptr)  { return complex_t(_mm_loadu_pd(ptr)); }
	void store(double* ptr)                   { _mm_store_pd(ptr, v); }
	void storeu(double* ptr)                  { _mm_storeu_pd(ptr, v); }

	complex_t& operator=(const complex_t& other) { v = other.v; return *this; }
	complex_t& operator+=(const complex_t& other) { v = _mm_add_pd(v, other.v); return *this; }
	complex_t& operator-=(const complex_t& other) { v = _mm_sub_pd(v, other.v); return *this; }
	complex_t& operator*=(const complex_t& other)
	{
		/*__m128d t1, res;
		t1  = _mm_mul_pd(this->v,other.v);               // t1 = xr*yr,      xi*yi
		res = _mm_hsub_pd(t1,t1);                // z  = (xr*yr - xi*yi), (xr*yr - xi*yi),
		t1  = _mm_shuffle_pd(other.v,other.v,0x1);       // t1 = yi, yr
		t1  = _mm_mul_pd(this->v,t1);                // t1 = xr*yi, xi*yr
		t1  = _mm_hadd_pd(t1,t1);                // t1 = xr*yi+xi*yr, xr*yi+xi*yr
		res = _mm_shuffle_pd(res,t1,0x2);        // t1 = xr*yr - xi*yi, xr*yi+xi*yr  (as desired)*/
		*this = (*this) * other; 
		return *this;
	}
	complex_t& operator*=(const double& other) { v = _mm_mul_pd(v, _mm_set1_pd(other)); return *this; }

	complex_t operator-()
	{
		return complex_t(
				_mm_xor_pd(this->v, conjugate_pd.v)
			);
	}

	static complex_t i()
	{
		return complex_t(0.0, 1.0);
	}

private:
	complex_t& operator/=(const complex_t& other) { v = _mm_div_pd(v, other.v); return *this; }
};

extern complex_t signmask_pd;
extern complex_t negate_one_pd;


inline complex_t operator+(const complex_t& a, const complex_t& b) { return complex_t(_mm_add_pd(a.v, b.v)); }
inline complex_t operator-(const complex_t& a, const complex_t& b) { return complex_t(_mm_sub_pd(a.v, b.v)); }
inline complex_t operator*(const complex_t& a, const complex_t& b)
{ 
#if 0
	__m128d t1, res;
	t1  = _mm_mul_pd(b.v,a.v);               // t1  = ar*br,      ai*bi
	res = _mm_hsub_pd(t1,t1);                // res = (ar*br - ai*bi), (ar*br - ai*bi),
	res = _mm_xor_pd(res, signmask_pd.v);
	t1  = _mm_shuffle_pd(b.v,b.v,0x1);       // t1  = yi, br
	t1  = _mm_mul_pd(a.v,t1);                // t1  = ar*bi, ai*br
	t1  = _mm_hadd_pd(t1,t1);                // t1  = ar*bi+ai*br, ar*bb+ai*br
	res = _mm_shuffle_pd(t1,res,0x2);        // res = ar*br - ai*bi, ar*bi+ai*br  (as desired)
	return complex_t(res);
#endif
#if 1
	__m128d t1, t2, t3;
	t1 = _mm_shuffle_pd(b.v, b.v, 0);
	t2 = _mm_shuffle_pd(b.v, b.v, 3);
	t3 = _mm_shuffle_pd(a.v, a.v, 1);
	t1  = _mm_mul_pd(t3, t1);
	t2  = _mm_mul_pd(a.v, t2);
	t1  = _mm_xor_pd(t1, negate_one_pd.v);
	t1  = _mm_add_pd(t1, t2);
	//t1  = _mm_addsub_pd(t1, t2);
	return complex_t(t1);
#endif

}
//inline complex_t operator/(const complex_t& a, const complex_t& b) { return complex_t(_mm_div_pd(a.v, b.v)); }
inline complex_t operator*(const complex_t& a, const double& b)
{
	return complex_t(_mm_mul_pd(a.v, _mm_set1_pd(b)));
}

inline complex_t operator*(const double& b, const complex_t& a)
{
	return complex_t(_mm_mul_pd(a.v, _mm_set1_pd(b)));
}


inline const double& re(const complex_t& a)
{
	return a.d[1];
}

inline const double& im(const complex_t& a)
{
	return a.d[0];
}
inline double& re(complex_t& a)
{
	return a.d[1];
}

inline double& im(complex_t& a)
{
	return a.d[0];
}

inline double arg(const complex_t& a)
{
	return zatan2d(re(a), im(a));
}

inline double mod(const complex_t& a)
{
	return zsqrtd(re(a)*re(a) + im(a)*im(a));
}

inline double magnitude(const complex_t& a)
{
	return mod(a);
}

inline double phase(const complex_t& a)
{
	return arg(a);
}
