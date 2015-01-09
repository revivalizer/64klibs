#include "pch.h"

ZMatrix ZeroMatrix(void)
{
	return ZMatrix(
		ZVector(0.f, 0.f, 0.f, 0.f),
		ZVector(0.f, 0.f, 0.f, 0.f),
		ZVector(0.f, 0.f, 0.f, 0.f),
		ZVector(0.f, 0.f, 0.f, 0.f));
}

ZMatrix IdentityMatrix(void)
{
	return ZMatrix(
		ZVector(1.f, 0.f, 0.f, 0.f),
		ZVector(0.f, 1.f, 0.f, 0.f),
		ZVector(0.f, 0.f, 1.f, 0.f),
		ZVector(0.f, 0.f, 0.f, 1.f));
}

ZMatrix TranslateMatrix(float x, float y, float z)
{
	return ZMatrix(
		ZVector(1.f, 0.f, 0.f, 0.f),
		ZVector(0.f, 1.f, 0.f, 0.f),
		ZVector(0.f, 0.f, 1.f, 0.f),
		ZVector(  x,   y,   z, 1.f));
}

ZMatrix TranslateMatrix(const ZVector& vec)
{
	return TranslateMatrix(vec[0], vec[1], vec[2]);
}

ZMatrix RotateXMatrix(float rad)
{
	float c = zcosf(rad);
	float s = zsinf(rad);

	return ZMatrix(
		ZVector(1.f, 0.f, 0.f, 0.f),
		ZVector(0.f,   c,   s, 0.f),
		ZVector(0.f,  -s,   c, 0.f),
		ZVector(0.f, 0.f, 0.f, 1.f));
}

ZMatrix RotateYMatrix(float rad)
{
	float c = zcosf(rad);
	float s = zsinf(rad);

	return ZMatrix(
		ZVector(  c, 0.f,  -s, 0.f),
		ZVector(0.f, 1.f, 0.f, 0.f),
		ZVector(  s, 0.f,   c, 0.f),
		ZVector(0.f, 0.f, 0.f, 1.f));
}

ZMatrix RotateZMatrix(float rad)
{
	float c = zcosf(rad);
	float s = zsinf(rad);

	return ZMatrix(
		ZVector(  c,   s, 0.f, 0.f),
		ZVector( -s,   c, 0.f, 0.f),
		ZVector(0.f, 0.f, 1.f, 0.f),
		ZVector(0.f, 0.f, 0.f, 1.f));
}

ZMatrix ScaleMatrix(float s)
{
	return ScaleMatrix(s, s, s);
}

ZMatrix ScaleMatrix(float x, float y, float z)
{
	return ZMatrix(
		ZVector(  x, 0.f, 0.f, 0.f),
		ZVector(0.f,   y, 0.f, 0.f),
		ZVector(0.f, 0.f,   z, 0.f),
		ZVector(0.f, 0.f, 0.f, 1.f));
}

ZMatrix LookAtMatrix(const ZVector& eye, const ZVector& center, const ZVector& pseudoup)
{
	// Look at gluLookAt for a reference for this
	ZVector forward = normalize(center-eye);
	ZVector right = normalize(cross(forward, pseudoup));
	ZVector up = cross(right, forward);

	ZMatrix mat;
	mat[0] = right;
	mat[1] = up;
	mat[2] = -forward;
	mat[3] = ZVector(0.0f);
	mat = mat.Transpose();

	//mat[3][3] = 1.f;
	//mat[3] = -eye;

	//mat = mat.Translate(-eye.v.f[0], -eye.v.f[1], -eye.v.f[2]);

	mat[3] = ZVector(dot(right, -eye), dot(up, -eye), dot(-forward, -eye), 1.0);

	return mat;
}

ZMatrix PerspectiveMatrix(float fovY, float aspect, float n, float f)
{
	float cot = 1.f / ztanf(deg2rad(fovY) / 2.f);   // 1/tan = cotangent
	ZMatrix mat = ZeroMatrix();
	mat.m[0][0] = cot/aspect;
	mat.m[1][1] = cot;
	mat.m[2][2] = (f + n) / (n - f);
	mat.m[2][3] = -1.f;
	mat.m[3][2] = (2.f * f * n) / (n - f);
	return mat;
}

ZMatrix PerspectiveMatrix(float left, float right, float bottom, float top, float n, float f)
{
	ZMatrix mat = ZeroMatrix();
	mat.m[0][0] = 2.f * n / (right - left);
	mat.m[1][1] = 2.f * n / (top - bottom);
	mat.m[2][0] = (right + left) / (right - left);
	mat.m[2][1] = (top + bottom) / (top - bottom);
	mat.m[2][2] = (f + n) / (n - f);
	mat.m[2][3] = -1.f;
	mat.m[3][2] = (2.f * f * n) / (n - f);
	return mat;
}

ZMatrix OrthoMatrix(float left, float right, float bottom, float top, float n, float f)
{
	ZMatrix mat = IdentityMatrix();
	mat.m[0][0] = 2.f / (right - left);
	mat.m[1][1] = 2.f / (top - bottom);
	mat.m[2][2] = -2.f / (f - n);
	mat.m[3][0] = -(right + left)/(right - left);
	mat.m[3][1] = -(top + bottom)/(top - bottom);
	mat.m[3][2] = -(f + n)/(f - n);
	return mat;
}

ZMatrix ZMatrix::Transpose() const
{
	// Microsoft specific macro that transposes in place
	ZMatrix res(*this);
	_MM_TRANSPOSE4_PS(res[0].v.v, res[1].v.v, res[2].v.v, res[3].v.v);
	return res;
}

ZMatrix ZMatrix::Translate(float x, float y, float z) const
{
	return (*this)*TranslateMatrix(x, y, z);
}

ZMatrix ZMatrix::Translate( const ZVector& vec ) const
{
	return (*this)*TranslateMatrix(vec);
}

ZMatrix ZMatrix::RotateX(float rad) const
{
	return (*this)*RotateXMatrix(rad);
}

ZMatrix ZMatrix::RotateY(float rad) const
{
	return (*this)*RotateYMatrix(rad);
}

ZMatrix ZMatrix::RotateZ(float rad) const
{
	return (*this)*RotateZMatrix(rad);
}

ZMatrix ZMatrix::Scale(float x, float y, float z) const
{
	return (*this)*ScaleMatrix(x, y, z);
}

ZMatrix ZMatrix::Scale(float s) const
{
	return (*this)*ScaleMatrix(s, s, s);
}

ZMatrix ZMatrix::OrthogonalInverse() const
{
	// Inverse rotation
	ZMatrix inverseRot = *this;
	inverseRot[3] = ZVector(0.f, 0.f, 0.f, 1.f);
	inverseRot = inverseRot.Transpose();

	// Inverse scale
	float lengths[3];
	lengths[0] = length(m[0]);
	lengths[1] = length(m[1]);
	lengths[2] = length(m[2]);

	ZMatrix inverseScale = IdentityMatrix();
	inverseScale[0][0] = 1.f/(lengths[0]*lengths[0]);
	inverseScale[1][1] = 1.f/(lengths[1]*lengths[1]);
	inverseScale[2][2] = 1.f/(lengths[2]*lengths[2]);

	// Inverse translation
	ZMatrix inverseTranslation = TranslateMatrix(-m[3]);

	return inverseScale * inverseRot * inverseTranslation;
}

ZMatrix operator*(const ZMatrix& a, const ZMatrix& b)
{
	// Look at this page, and specifically anonymous' comment to understand how this works: http://fhtr.blogspot.dk/2010/02/4x4-float-matrix-multiplication-using.html
	ZMatrix res;

	ZMatrix ta = ZMatrix(a).Transpose();

	for (uint32_t i=0; i<4; i++)
	{
		res[i] = ZVector(_mm_hadd_ps(
							_mm_hadd_ps(
								(b[i]*ta[0]).v.v,
								(b[i]*ta[1]).v.v), 
							_mm_hadd_ps(
								(b[i]*ta[2]).v.v, 
								(b[i]*ta[3]).v.v)));
	}

	return res;
}

ZVector operator*(const ZMatrix& a, const ZVector& b)
{
	// Look at this page, and specifically anonymous' comment to understand how this works: http://fhtr.blogspot.dk/2010/02/4x4-float-matrix-multiplication-using.html
	ZVector res;

	ZMatrix ta = ZMatrix(a).Transpose();
	//ZMatrix tb = ZMatrix(b).Transpose();

	//for (uint32_t i=0; i<4; i++)
	{
		res    = ZVector(_mm_hadd_ps(
							_mm_hadd_ps(
								(ta[0]*b).v.v,
								(ta[1]*b).v.v), 
							_mm_hadd_ps(
								(ta[2]*b).v.v, 
								(ta[3]*b).v.v)));
	}

	return res;
}

ZMatrix Mul(const ZMatrix& a, const ZMatrix& b)
{
	return a*b;
}

ZVector Mul(const ZMatrix& a, const ZVector& b)
{
	return a*b;
}

ZMatrix MatrixFromVectors(const ZVector& right, const ZVector& up, const ZVector& forward, const ZVector& pos)
{
	ZMatrix mat;
	mat[0] = right;
	mat[1] = up;
	mat[2] = forward;
	mat[3] = ZVector(0.0f);
	//mat = mat.Transpose();
	mat[3] = pos;
	mat[3][3] = 1.f;

	return mat;
}

ZMatrix MakeNormalMatrix(const ZMatrix& mat)
{
	auto nm = mat;
	nm[3] = ZVector(0.f, 0.f, 0.f, 1.f);
	nm    = nm.OrthogonalInverse().Transpose();
	return nm;
}
