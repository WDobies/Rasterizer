#pragma once
#include "Vector4.h"
class Matrix4
{
public:
	Vector4 col1, col2, col3, col4;

	Matrix4();
	Matrix4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4);

	Vector4 operator *(const Vector4& b)const;

	Matrix4& Perspective(float fov, float aspect, float near, float far);

	Matrix4 LookAt(Vector3 eye, Vector3 center, Vector3 up = Vector3(0,1,0));

	static Matrix4 Translate(Matrix4 m1, Vector3 v);
	static Matrix4 Scale(Matrix4 m1, Vector3 v);
	static Matrix4 Rotate(Matrix4 m1, Vector3 axis, float angle);

	Matrix4 operator *(const Matrix4& m2)const;
	static Matrix4 Identity();

	std::string ToString()const;
};

