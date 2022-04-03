#pragma once
#include "Vector4.h"
class Matrix4
{
public:
	Vector4 col1, col2, col3, col4;

	Matrix4();
	Matrix4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4);

	Vector4 operator * (const Vector4& b)const;

	Matrix4& Perspective(float fov, float aspect, float near, float far);

	std::string ToString()const;
};

