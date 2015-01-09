#pragma once

// Double functions

double zlog10d(const double x);
double zlog2d(const double x);
double zlogd(const double x);
double zexpd(const double x);
double zfmodd(const double x, const double y);
double zpowd(const double x, const double y);

// THANKS: These are also from IQ
ZINLINE double zsind(const double x) { double r; _asm fld  qword ptr [x]; 
                                                 _asm fsin;  
                                                 _asm fstp qword ptr [r]; 
                                                 return r; }
ZINLINE double zcosd(const double x) { double r; _asm fld  qword ptr [x]; 
                                                 _asm fcos; 
                                                 _asm fstp qword ptr [r]; 
                                                 return r; }
ZINLINE double zsqrtd(const double x) { double r; _asm fld  qword ptr [x]; 
                                                  _asm fsqrt; 
                                                  _asm fstp qword ptr [r]; 
                                                  return r; }
ZINLINE double zfabsd(const double x) { double r; _asm fld  qword ptr [x]; 
                                                  _asm fabs;  
                                                  _asm fstp qword ptr [r]; 
                                                  return r; }
ZINLINE double ztand( const double x) { double r; _asm fld  qword ptr [x];
                                                  _asm fptan;  
                                                  _asm fstp st(0)
                                                  _asm fstp qword ptr [r];
                                                  return r; }

ZINLINE double zatan2d( const double x, const double y) { double r; _asm fld qword ptr [y];
                                                                    _asm fld qword ptr [x]
                                                                    _asm fpatan;
                                                                    _asm fstp qword ptr [r];
                                                                    return r; }

// Float functions

float zlog10f(const float x);
float zlog2f(const float x);
float zlogf(const float x);
float zexpf(const float x);
float zfmodf(const float x, const float y);
float zpowf(const float x, const float y);

// THANKS: These are also from IQ
ZINLINE float zsinf(const float x) { float r; _asm fld  dword ptr [x]; 
                                                       _asm fsin;  
                                                       _asm fstp dword ptr [r]; 
                                                       return r; }
ZINLINE float zcosf(const float x) { float r; _asm fld  dword ptr [x]; 
                                                       _asm fcos; 
                                                       _asm fstp dword ptr [r]; 
                                                       return r; }
ZINLINE float zsqrtf(const float x) { float r; _asm fld  dword ptr [x]; 
                                                       _asm fsqrt; 
                                                       _asm fstp dword ptr [r]; 
                                                       return r; }
ZINLINE float zfabsf(const float x) { float r; _asm fld  dword ptr [x]; 
                                                       _asm fabs;  
                                                       _asm fstp dword ptr [r]; 
                                                       return r; }
#pragma warning(disable: 4725) 
ZINLINE float ztanf( const float x) { float r; _asm fld  dword ptr [x];
                                                       _asm fptan;  
                                                       _asm fstp st(0)
                                                       _asm fstp dword ptr [r];
                                                       return r; }

// Simpler to use the fisttp opcodes, which works on SSE3.
// Truncates towards 0, ala C cast.
// For negative values, this is not how the usual C floor function works
ZINLINE int32_t zitruncf(const float x)
{
	int32_t r;
    _asm fld     dword ptr [x]
    _asm fisttp   dword ptr [r]
	return r;
}

ZINLINE int64_t zltruncf(const float x)
{
	int64_t r;
    _asm fld     dword ptr [x]
    _asm fisttp   qword ptr [r]
	return r;
}

ZINLINE int32_t zitruncd(const double x)
{
	int32_t r;
    _asm fld     qword ptr [x]
    _asm fisttp   dword ptr [r]
	return r;
}

ZINLINE int64_t zltruncd(const double x)
{
	int64_t r;
    _asm fld     qword ptr [x]
    _asm fisttp   qword ptr [r]
	return r;
}

// http://www.codeproject.com/Tips/700780/Fast-floor-ceiling-functions
// shift values to positive range
// no error checking here, range is limited
// but of course this is also true of regular floor, trunc and so on

static const int32_t shift32 = 1073741824;

ZINLINE int32_t zifloord(const double x)
{
	// shift out of negative range
	return zitruncd(x + 1073741824.) - 1073741824;
}

// Here we use the property that floor(-fp) = -ceiling(fp) 
ZINLINE int32_t ziceild(const double x)
{
	// shift out of negative range
	return 1073741824 - zitruncd(1073741824. - x);
}

ZINLINE int32_t ziroundd(const double x)
{
	// unbiased round
	return zifloord(x + 0.5);
}

template<class T>
ZINLINE T zabs(const T& a)
{
	if (a < T(0))
		return -a;
	else
		return a;
}

template<class T>
ZINLINE T zmax(const T& a, const T& b)
{
	if (a > b)
		return a;
	else
		return b;
}

template<class T>
ZINLINE T zmin(const T& a, const T& b)
{
	if (a < b)
		return a;
	else
		return b;
}

template<class T>
ZINLINE T zclamp(const T& value, const T& min, const T& max)
{
	return zmax(min, zmin(max, value));
}

/*ZINLINE double zmax(double a, double b)
{
	if (a > b)
		return a;
	else
		return b;
}

ZINLINE double zmin(double a, double b)
{
	if (a < b)
		return a;
	else
		return b;
}

ZINLINE double zclamp(double value, double min, double max)
{
	return zmax(min, zmin(max, value));
}*/

// From this SO answer: http://stackoverflow.com/a/6566033
ZINLINE double zmin( double a, double b )
{
    // Branchless SSE min.
    _mm_store_sd( &a, _mm_min_sd(_mm_set_sd(a),_mm_set_sd(b)) );
    return a;
}

ZINLINE double zmax ( double a, double b )
{
    // Branchless SSE max.
    _mm_store_sd( &a, _mm_max_sd(_mm_set_sd(a),_mm_set_sd(b)) );
    return a;
}

ZINLINE double zclamp ( double val, double minval, double maxval )
{
    // Branchless SSE clamp.
    // return minss( maxss(val,minval), maxval );

    _mm_store_sd( &val, _mm_min_sd( _mm_max_sd(_mm_set_sd(val),_mm_set_sd(minval)), _mm_set_sd(maxval) ) );
    return val;
}


