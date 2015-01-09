#pragma once

class ZQuaternion {
protected:
    __m128 xmm; // vector of 4 single precision floats
public:
    // default constructor
    ZQuaternion() {
    }
    // construct from real and imaginary parts = re + im0*i + im1*j + im2*k
    ZQuaternion(float re, float im0, float im1, float im2) {
        xmm = vec4f_t(re, im0, im1, im2);
    }
    // construct from real, no imaginary part
    ZQuaternion(float re) {
        xmm = _mm_load_ss(&re);
    }
    // Constructor to convert from type __m128 used in intrinsics:
    ZQuaternion(__m128 const & x) {
        xmm = x;
    }
    // Assignment operator to convert from type __m128 used in intrinsics:
    ZQuaternion & operator = (__m128 const & x) {
        xmm = x;
        return *this;
    }
    // Constructor to convert from vec4f_t
    ZQuaternion(vec4f_t const & x) {
        xmm = x;
    }
    // Type cast operator to convert to __m128 used in intrinsics
    operator __m128() const {
        return xmm;
    }
    // Member function to convert to vector
    vec4f_t to_vector() const {
        return xmm;
    }
    // Member function to load from array (unaligned)
    ZQuaternion & loadu(float const * p) {
        xmm = vec4f_t::loadu(p);
        return *this;
    }

    // Member function to load from array, aligned by 16
    ZQuaternion const & load(float const * p) {
        xmm = vec4f_t::load(p);
        return *this;
    }

    // Member function to store into array (unaligned)
    void storeu(float * p) const {
        vec4f_t(xmm).storeu(p);
    }

    // Member function to store into array, aligned by 16
    void store(float * p) const {
        vec4f_t(xmm).store(p);
    }

    // Member function to extract real part
    float real() const {
        return _mm_cvtss_f32(xmm);
    }
    // Member function to extract imaginary parts, sets real part to 0
    ZQuaternion imag() const {
        return ZQuaternion(permute4f<-1,1,2,3>(vec4f_t(xmm)));
    }
    // Member function to extract one real or imaginary part
    float extract(uint32_t index) const {
        float x[4];
        vec4f_t(xmm).store(x);
        return x[index & 3];
    }
};


/*****************************************************************************
*
*          Operators for ZQuaternion
*
*****************************************************************************/

// operator + : add
static inline ZQuaternion operator + (ZQuaternion const & a, ZQuaternion const & b) {
    return ZQuaternion(a.to_vector() + b.to_vector());
}

// operator += : add
static inline ZQuaternion & operator += (ZQuaternion & a, ZQuaternion const & b) {
    a = a + b;
    return a;
}

// operator - : subtract
static inline ZQuaternion operator - (ZQuaternion const & a, ZQuaternion const & b) {
    return ZQuaternion(a.to_vector() - b.to_vector());
}

// operator - : unary minus
static inline ZQuaternion operator - (ZQuaternion const & a) {
    return ZQuaternion(- a.to_vector());
}

// operator -= : subtract
static inline ZQuaternion & operator -= (ZQuaternion & a, ZQuaternion const & b) {
    a = a - b;
    return a;
}

// operator * : quaternion multiply
static inline ZQuaternion operator * (ZQuaternion const & a, ZQuaternion const & b) {
    __m128 a1123 = _mm_shuffle_ps(a,a,0xE5);
    __m128 a2231 = _mm_shuffle_ps(a,a,0x7A);
    __m128 b1000 = _mm_shuffle_ps(b,b,0x01);
    __m128 b2312 = _mm_shuffle_ps(b,b,0x9E);
    __m128 t1    = _mm_mul_ps(a1123, b1000);
    __m128 t2    = _mm_mul_ps(a2231, b2312);
    __m128 t12   = _mm_add_ps(t1, t2);
    __m128 t12m  = change_sign<1,0,0,0>(vec4f_t(t12));
    __m128 a3312 = _mm_shuffle_ps(a,a,0x9F);
    __m128 b3231 = _mm_shuffle_ps(b,b,0x7B);
    __m128 a0000 = _mm_shuffle_ps(a,a,0x00);
    __m128 t3    = _mm_mul_ps(a3312, b3231);
    __m128 t0    = _mm_mul_ps(a0000, b);
    __m128 t03   = _mm_sub_ps(t0, t3);
    return         _mm_add_ps(t03, t12m);
}

// operator *= : multiply
static inline ZQuaternion & operator *= (ZQuaternion & a, ZQuaternion const & b) {
    a = a * b;
    return a;
}

// operator ~ : complex conjugate
// ~(a + b*i + c*j + d*k) = (a - b*i - c*j - d*k)
static inline ZQuaternion operator ~ (ZQuaternion const & a) {
    return ZQuaternion(change_sign<0,1,1,1>(a.to_vector()));
}

// function reciprocal: multiplicative inverse
static inline ZQuaternion reciprocal (ZQuaternion const & a) {
    vec4f_t sq  = _mm_mul_ps(a,a);
    float nsq = horizontal_add(sq);
    return ZQuaternion((~a).to_vector() / vec4f_t(nsq));
}

// operator / : quaternion divide is defined as
// a / b = a * reciprocal(b)
static inline ZQuaternion operator / (ZQuaternion const & a, ZQuaternion const & b) {
    return a * reciprocal(b);
}

// operator /= : divide
static inline ZQuaternion & operator /= (ZQuaternion & a, ZQuaternion const & b) {
    a = a / b;
    return a;
}

/*
// operator == : returns true if a == b
static inline bool operator == (ZQuaternion const & a, ZQuaternion const & b) {
    vec4f_tb t1 = a.to_vector() == b.to_vector();
    return horizontal_and(t1);
}

// operator != : returns true if a != b
static inline bool operator != (ZQuaternion const & a, ZQuaternion const & b) {
    vec4f_tb t1 = a.to_vector() != b.to_vector();
    return horizontal_or(t1);
}*/


/*****************************************************************************
*
*          Operators mixing ZQuaternion and float
*
*****************************************************************************/

// operator + : add
static inline ZQuaternion operator + (ZQuaternion const & a, float b) {
    return _mm_add_ss(a, _mm_set_ss(b));
}

static inline ZQuaternion operator + (float a, ZQuaternion const & b) {
    return b + a;
}

static inline ZQuaternion & operator += (ZQuaternion & a, float & b) {
    a = a + b;
    return a;
}

// operator - : subtract
static inline ZQuaternion operator - (ZQuaternion const & a, float b) {
    return _mm_sub_ss(a, _mm_set_ss(b));
}

static inline ZQuaternion operator - (float a, ZQuaternion const & b) {
    return _mm_sub_ps(_mm_set_ss(a), b);
}

static inline ZQuaternion & operator -= (ZQuaternion & a, float & b) {
    a = a - b;
    return a;
}

// operator * : multiply
static inline ZQuaternion operator * (ZQuaternion const & a, float b) {
    return _mm_mul_ps(a, _mm_set1_ps(b));
}

static inline ZQuaternion operator * (float a, ZQuaternion const & b) {
    return b * a;
}

static inline ZQuaternion & operator *= (ZQuaternion & a, float & b) {
    a = a * b;
    return a;
}

// operator / : divide
static inline ZQuaternion operator / (ZQuaternion const & a, float b) {
    return _mm_div_ps(a, _mm_set1_ps(b));
}

static inline ZQuaternion operator / (float a, ZQuaternion const & b) {
    return reciprocal(b) * a;
}

static inline ZQuaternion & operator /= (ZQuaternion & a, float b) {
    a = a / b;
    return a;
}


/*****************************************************************************
*
*          Functions for ZQuaternion
*
*****************************************************************************/

// function abs: calculate the norm
// abs(a + b*i + c*j + d*k) = sqrt(a*a + b*B + c*c + d*d)
static inline ZQuaternion abs(ZQuaternion const & a) {
    vec4f_t sq  = _mm_mul_ps(a,a);
    float nsq = horizontal_add(sq);
    return zsqrtf(nsq);
}

// function select
static inline ZQuaternion select (bool s, ZQuaternion const & a, ZQuaternion const & b) {
    return ZQuaternion(s ? a : b);
}
