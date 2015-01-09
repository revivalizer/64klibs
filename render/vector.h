#pragma once

class ZVector : public align16
{
public:
	ZVector(void) {}
	explicit ZVector(const float* x)        : v(((uintptr_t(x) & 0xf)==0) ? vec4f_t::load(x) : vec4f_t::loadu(x)) {}
	explicit ZVector(float x)               : v(x) {}
	explicit ZVector(const __m128& in)      : v(in) {}
	explicit ZVector(const vec4f_t& in)     : v(in) {}
	         ZVector(const ZVector& x)      : v(x.v) {}
	         ZVector(float x1, float x2)                     : v(x1,  x2, 0.f, 0.f) {}
	         ZVector(float x1, float x2, float x3)           : v(x1,  x2,  x3, 0.f) {}
	         ZVector(float x1, float x2, float x3, float x4) : v(x1,  x2,  x3,  x4) {}

	static ZVector MakeVec3(const ZVector& other, float n) { return ZVector(other.v.f[0], other.v.f[1], n, 0.f); }          // Makes a vec3 by extending a vec2 with a float
	static ZVector MakeVec4(const ZVector& other, float n) { return ZVector(other.v.f[0], other.v.f[1], other.v.f[2], n); } // Makes a vec4 by extending a vec3 with a float

	ZVector& operator= (const ZVector& other) { v  = other.v; return *this; }

	ZVector& operator+=(const ZVector& other) { v += other.v; return *this; }
	ZVector& operator-=(const ZVector& other) { v -= other.v; return *this; }
	ZVector& operator*=(const ZVector& other) { v *= other.v; return *this; }
	ZVector& operator/=(const ZVector& other) { v /= other.v; return *this; }

	ZVector& operator+=(const float other) { v += vec4f_t(other); return *this; }
	ZVector& operator-=(const float other) { v -= vec4f_t(other); return *this; }
	ZVector& operator*=(const float other) { v *= vec4f_t(other); return *this; }
	ZVector& operator/=(const float other) { v /= vec4f_t(other); return *this; }

	ZVector operator-() const
	{
		return ZVector(-v);
	}

	      float& operator[](uint32_t i)       { return v.f[i]; }
	const float& operator[](uint32_t i) const { return v.f[i]; }

public:
	vec4f_t v;
};

inline ZVector operator+(const ZVector& a, const ZVector& b) { return ZVector(a.v + b.v); }
inline ZVector operator-(const ZVector& a, const ZVector& b) { return ZVector(a.v - b.v); }
inline ZVector operator*(const ZVector& a, const ZVector& b) { return ZVector(a.v * b.v); }
inline ZVector operator/(const ZVector& a, const ZVector& b) { return ZVector(a.v / b.v); }

inline ZVector operator+(const ZVector& a, const float b) { return ZVector(a.v + vec4f_t(b)); }
inline ZVector operator-(const ZVector& a, const float b) { return ZVector(a.v - vec4f_t(b)); }
inline ZVector operator*(const ZVector& a, const float b) { return ZVector(a.v * vec4f_t(b)); }
inline ZVector operator/(const ZVector& a, const float b) { return ZVector(a.v / vec4f_t(b)); }

inline ZVector cross(const ZVector& a, const ZVector& b) { return ZVector(cross(a.v, b.v)); }
inline float   dot(const ZVector& a, const ZVector& b) { return dot(a.v, b.v); }
inline float   length(const ZVector& a) { return length(a.v); }
inline ZVector normalize(const ZVector& a) { return ZVector(normalize(a.v)); }

inline ZVector scale(const ZVector& a, float s) { return a*s; }

inline ZVector setlength(const ZVector& a, float l) { return scale(a, l/length(a)); }
