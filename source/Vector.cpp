#include "Vector.h"

CVector::CVector() {
	X = 0;
	Y = 0;
	Z = 0;
}

CVector::CVector(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}

CVector::CVector(VERTEX vertex) {
	X = vertex.x;
	Y = vertex.y;
	Z = vertex.z;
}

CVector::~CVector(void)
{
}

void CVector::Normalize() {
	float lon = Magnitude();

	X /= lon;
	Y /= lon;
	Z /= lon;
}

__inline const float CVector::Magnitude() const {
	return (float)sqrt(((X)*(X))+((Y)*(Y))+((Z)*(Z)));
}

CVector CVector::operator+ (const CVector &v1) const {
	return CVector(X + v1.X, Y + v1.Y, Z + v1.Z);
}

CVector CVector::operator- (const CVector &v1) const {
	return CVector(X - v1.X, Y - v1.Y, Z - v1.Z);
}

CVector CVector::operator* (const CVector &v1) const {
	return CVector(X * v1.X, Y * v1.Y, Z * v1.Z);
}

CVector CVector::operator/ (const CVector &v1) const {
	return CVector(X / v1.X, Y / v1.Y, Z / v1.Z);
}

CVector CVector::operator* (const float f) const {
	return CVector(X*f, Y*f, Z*f);
}

CVector CVector::operator/ (const float f) const {
	return CVector(X/f, Y/f, Z/f);
}

void CVector::operator= (const CVector &v) {
	X = v.X;
	Y = v.Y;
	Z = v.Z;
}

void CVector::operator= (const VERTEX &v) {
	X = v.x;
	Y = v.y;
	Z = v.z;
}