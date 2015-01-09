#pragma once

class ZMatrix : public align16
{
public:
	ZMatrix(void) {}

	//ZMatrix(const mat4f_t& other);

	ZMatrix(const float* x) { m[0] = ZVector(&(x[0])); m[1] = ZVector(&(x[4])); m[2] = ZVector(&(x[8])); m[3] = ZVector(&(x[12])); }
	ZMatrix(const ZVector (&x)[4]) { m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = x[3]; }
	ZMatrix(const ZVector& x1, const ZVector& x2, const ZVector& x3, const ZVector& x4) { m[0] = x1; m[1] = x2; m[2] = x3; m[3] = x4; }

	ZMatrix Translate(float x, float y, float z) const;
	ZMatrix Translate(const ZVector& vec) const;
	ZMatrix RotateX(float rad) const; 
	ZMatrix RotateY(float rad) const;
	ZMatrix RotateZ(float rad) const;
	ZMatrix Scale(float x, float y, float z) const;
	ZMatrix Scale(float s) const;

	ZMatrix Transpose() const;
	ZMatrix OrthogonalInverse() const;

	      ZVector& operator[](uint32_t i)       { return m[i]; }
	const ZVector& operator[](uint32_t i) const { return m[i]; }

public:
	ZVector m[4];
};

ZMatrix operator*(const ZMatrix& b, const ZMatrix& a);
ZVector operator*(const ZMatrix& b, const ZVector& a);

ZMatrix Mul(const ZMatrix& b, const ZMatrix& a);
ZVector Mul(const ZMatrix& b, const ZVector& a);

ZMatrix ZeroMatrix(void);
ZMatrix IdentityMatrix(void);
ZMatrix TranslateMatrix(float x, float y, float z);
ZMatrix TranslateMatrix(const ZVector& vec);
ZMatrix RotateXMatrix(float rad); 
ZMatrix RotateYMatrix(float rad);
ZMatrix RotateZMatrix(float rad);
ZMatrix ScaleMatrix(float x, float y, float z);
ZMatrix ScaleMatrix(float s);
ZMatrix LookAtMatrix(const ZVector& eye, const ZVector& center, const ZVector& pseudoup);
ZMatrix PerspectiveMatrix(float fovY, float aspect, float n, float f);
ZMatrix PerspectiveMatrix(float left, float right, float bottom, float top, float n, float f);
ZMatrix OrthoMatrix(float left, float right, float bottom, float top, float n, float f);
ZMatrix MatrixFromVectors(const ZVector& right, const ZVector& up, const ZVector& forward, const ZVector& pos);
//ZMatrix MakeRotationAxis(const ZVector& axis, float angle);
//ZMatrix MakeFromNormalizedBases(const ZVector& x, const ZVector& y, const ZVector& z);

ZMatrix MakeNormalMatrix(const ZMatrix& mat);