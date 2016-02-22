#pragma once

#include "util.h"

class CVector;

class CVector
{
public:
	float X, Y, Z;

	CVector();
	CVector(float x, float y, float z);
	CVector(VERTEX vertex);
	~CVector(void);

	CVector operator+ (const CVector &v1) const;
	CVector operator- (const CVector &v1) const;
	CVector operator* (const CVector &v1) const;
	CVector operator/ (const CVector &v1) const;

	CVector operator* (const float f) const;
	CVector operator/ (const float f) const;

	void operator= (const CVector &v);
	void operator= (const VERTEX &v);

	void Normalize();

	__inline const float Magnitude() const;
};
