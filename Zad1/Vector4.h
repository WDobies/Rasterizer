#pragma once
#include "Vector3.h"
class Vector4
{
public:
	float x, y, z, w;

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 zyx, float w = 1);

	Vector4 operator * (const Vector4& b)const;

	Vector4 operator*(const Vector3& b) const;

	Vector4 operator *(float k) const;

	Vector4& operator*=(float k);
	Vector4& operator+=(const Vector4 v);

	Vector4& operator+=(const Vector3 v);

	static Vector4 One();

	std::string ToString() const;

};

