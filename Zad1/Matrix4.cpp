#include "Matrix4.h"
#include <iostream>

Matrix4::Matrix4()
{
	*this = Matrix4::Identity();
}

Matrix4::Matrix4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4)
{
	this->col1 = col1;
	this->col2 = col2;
	this->col3 = col3;
	this->col4 = col4;
}

Vector4 Matrix4::operator*(const Vector4& b) const
{
	float row1 = col1.x * b.x + col2.x * b.y + col3.x * b.z + col4.x * b.w;
	float row2 = col1.y * b.x + col2.y * b.y + col3.y * b.z + col4.y * b.w;
	float row3 = col1.z * b.x + col2.z * b.y + col3.z * b.z + col4.z * b.w;
	float row4 = col1.w * b.x + col2.w * b.y + col3.w * b.z + col4.w * b.w;

	return Vector4(row1,row2,row3,row4);
}

Matrix4& Matrix4::Perspective(float fov, float aspect, float near, float far)
{
	fov *= 3.14 / 360.f;
	float f = cos(fov) / sin(fov);
	col1 = Vector4(f / aspect, 0, 0, 0);
	col2 = Vector4(0, f, 0, 0);
	col3 = Vector4(0, 0, (far + near) / (near - far),  1);
	col4 = Vector4(0, 0, (2*far*near) / (near - far),  0);
	return *this;
}

Matrix4 Matrix4::LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 f = eye - center;
	f = Vector3::Normalize(f);
	up = Vector3::Normalize(up);
	Vector3 s = Vector3::Cross(f, up);
	Vector3 u = Vector3::Cross(s, f);

	Matrix4 m;
	m.col1 = Vector4(s.x, u.x, -f.x, 0);
	m.col2 = Vector4(s.y, u.y, -f.y, 0);
	m.col3 = Vector4(s.z, u.z, -f.z, 0);
	m.col4 = Vector4(0,0,0,1);

	Matrix4 es;
	es.col4 = Vector4(-eye.x, -eye.y, -eye.z, 1);

	return m*es;
}

Matrix4 Matrix4::Translate(Matrix4 m1, Vector3 v)
{
	Vector4 c1(1, 0, 0, 0);
	Vector4 c2(0, 1, 0, 0);
	Vector4 c3(0, 0, 1, 0);
	Vector4 c4(v.x, v.y, v.z, 1);
	Matrix4 translate(c1,c2,c3,c4);

	return m1 * translate;
}

Matrix4 Matrix4::Scale(Matrix4 m1, Vector3 v)
{
	m1.col1 *= v.x;
	m1.col2 *= v.y;
	m1.col3 *= v.z;

	return m1;
}

Matrix4 Matrix4::Rotate(Matrix4 m1, Vector3 axis, float angle)
{
	//angle = angle * 3.141592f / 180.0f;
	axis = Vector3::Normalize(axis);
	float s = sin(angle * 3.141592f / 180.0f);
	float c = cos(angle * 3.141592f / 180.0f);

	float e1 = axis.x * axis.x * (1 - c) + c;
	float e2 = axis.x * axis.y * (1 - c) - axis.z * s;
	float e3 = axis.x * axis.z * (1 - c) + axis.y * s;

	float e5 = axis.y * axis.x * (1 - c) + axis.z * s;
	float e6 = axis.y * axis.y * (1 - c) + c;
	float e7 = axis.y * axis.z * (1 - c) - axis.x * s;

	float e9 =  axis.x * axis.z * (1 - c) - axis.y * s;
	float e10 = axis.y * axis.z * (1 - c) + axis.x * s;
	float e11 = axis.z * axis.z * (1 - c) + c;

	Vector4 c1(e1, e5, e9, 0);
	Vector4 c2(e2, e6, e10, 0);
	Vector4 c3(e3, e7, e11, 0);
	Vector4 c4(0, 0, 0, 1);
	
	Matrix4 rotation(c1, c2, c3, c4);

	//m1.col1.x *= e1;
	//m1.col1.y *= e5;
	//m1.col1.z *= e9;

	//m1.col2.x *= e2;
	//m1.col2.y *= e6;
	//m1.col2.z *= e10;

	//m1.col4.x *= e3;
	//m1.col4.y *= e7;
	//m1.col4.z *= e11;

	return m1 * rotation;
}

Matrix4 Matrix4::operator*(const Matrix4& m2) const
{

	float e1 = col1.x * m2.col1.x + col2.x * m2.col1.y + col3.x * m2.col1.z + col4.x * m2.col1.w;
	float e2 = col1.y * m2.col1.x + col2.y * m2.col1.y + col3.y * m2.col1.z + col4.y * m2.col1.w;
	float e3 = col1.z * m2.col1.x + col2.z * m2.col1.y + col3.z * m2.col1.z + col4.z * m2.col1.w;
	float e4 = col1.w * m2.col1.x + col2.w * m2.col1.y + col3.w * m2.col1.z + col4.w * m2.col1.w;

	float e5 = col1.x * m2.col2.x + col2.x * m2.col2.y + col3.x * m2.col2.z + col4.x * m2.col2.w;
	float e6 = col1.y * m2.col2.x + col2.y * m2.col2.y + col3.y * m2.col2.z + col4.y * m2.col2.w;
	float e7 = col1.z * m2.col2.x + col2.z * m2.col2.y + col3.z * m2.col2.z + col4.z * m2.col2.w;
	float e8 = col1.w * m2.col2.x + col2.w * m2.col2.y + col3.w * m2.col2.z + col4.w * m2.col2.w;

	float e9  = col1.x * m2.col3.x + col2.x * m2.col3.y + col3.x * m2.col3.z + col4.x * m2.col3.w;
	float e10 = col1.y * m2.col3.x + col2.y * m2.col3.y + col3.y * m2.col3.z + col4.y * m2.col3.w;
	float e11 = col1.z * m2.col3.x + col2.z * m2.col3.y + col3.z * m2.col3.z + col4.z * m2.col3.w;
	float e12 = col1.w * m2.col3.x + col2.w * m2.col3.y + col3.w * m2.col3.z + col4.w * m2.col3.w;

	float e13 = col1.x * m2.col4.x + col2.x * m2.col4.y + col3.x * m2.col4.z + col4.x * m2.col4.w;
	float e14 = col1.y * m2.col4.x + col2.y * m2.col4.y + col3.y * m2.col4.z + col4.y * m2.col4.w;
	float e15 = col1.z * m2.col4.x + col2.z * m2.col4.y + col3.z * m2.col4.z + col4.z * m2.col4.w;
	float e16 = col1.w * m2.col4.x + col2.w * m2.col4.y + col3.w * m2.col4.z + col4.w * m2.col4.w;

	Vector4 c1(e1, e2, e3, e4);
	Vector4 c2(e5, e6, e7, e8);
	Vector4 c3(e9, e10, e11, e12);
	Vector4 c4(e13, e14, e15, e16);

	return Matrix4(c1, c2, c3, c4);
}

Matrix4 Matrix4::Identity()
{
	Vector4 c1(1, 0, 0, 0);
	Vector4 c2(0, 1, 0, 0);
	Vector4 c3(0, 0, 1, 0);
	Vector4 c4(0, 0, 0, 1);

	return Matrix4(c1,c2,c3,c4);
}


std::string Matrix4::ToString() const
{
	std::string text = std::to_string(col1.x) + " " + std::to_string(col2.x) + " " + std::to_string(col3.x) + " " + std::to_string(col4.x) + "\n ";
				text += std::to_string(col1.y) + " " + std::to_string(col2.y) + " " + std::to_string(col3.y) + " " + std::to_string(col4.y) + "\n ";
				text += std::to_string(col1.z) + " " + std::to_string(col2.z) + " " + std::to_string(col3.z) + " " + std::to_string(col4.z) + "\n ";
				text += std::to_string(col1.w) + " " + std::to_string(col2.w) + " " + std::to_string(col3.w) + " " + std::to_string(col4.w) + "\n";
	return text;
}
