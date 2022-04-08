#include "Matrix4.h"
#include <iostream>

Matrix4::Matrix4()
{
	this->col1 = Vector4::One();
	this->col2 = Vector4::One();
	this->col3 = Vector4::One();
	this->col4 = Vector4::One();
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
	float row1 = col1.x * b.x + col1.y * b.y + col1.z * b.z + col1.w * b.w;
	float row2 = col2.x * b.x + col2.y * b.y + col2.z * b.z + col2.w * b.w;
	float row3 = col3.x * b.x + col3.y * b.y + col3.z * b.z + col3.w * b.w;
	float row4 = col4.x * b.x + col4.y * b.y + col4.z * b.z + col4.w * b.w;

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

Matrix4& Matrix4::LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 f = center - eye;
	f = Vector3::Normalize(f);
	up = Vector3::Normalize(up);
	Vector3 s = Vector3::Cross(f, up);
	Vector3 u = Vector3::Cross(s, f);
	col1 = Vector4(s.x, u.x, -f.x, 0);
	col2 = Vector4(s.y, u.y, -f.y, 0);
	col3 = Vector4(s.z, u.z, -f.z, 0);
	col4 = Vector4(-eye.x, -eye.y, -eye.z,1);

	return *this;
	
}

Matrix4 Matrix4::Translate(Matrix4 m1, Vector3 v)
{
	m1.col1.w += v.x;
	m1.col2.w += v.y;
	m1.col3.w += v.z;
	return m1;
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
	angle = angle * 3.14 / 360.0f;
	//std::cout << angle;
;	m1.col1.x *= cos(angle) + axis.x * axis.x * (1 - cos(angle));
	m1.col1.y *= axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle);
	m1.col1.z *= axis.x * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
	m1.col1.w *= 0;

	m1.col2.x *= axis.y * axis.x * (1 - cos(angle)) - axis.z * sin(angle);
	m1.col2.y *= cos(angle) + axis.y * axis.y * (1 - cos(angle));
	m1.col2.z *= axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
	m1.col2.w *= 0;

	m1.col3.x *= axis.z * axis.x * (1 - cos(angle)) - axis.y * sin(angle);
	m1.col3.y *= axis.z * axis.y * (1 - cos(angle)) - axis.x * sin(angle);
	m1.col3.z *= cos(angle) + axis.z * axis.z * (1 - cos(angle));
	m1.col3.w *= 0;

	m1.col4 = m1.col4 * Vector4(0, 0, 0, 1);

	return m1;
}

Matrix4 Matrix4::Mul(Matrix4 m1, Matrix4 m2)
{

	float e1 = m1.col1.x * m2.col1.x + m1.col2.x * m2.col1.y + m1.col3.x * m2.col1.z + m1.col4.x * m2.col1.w;
	float e2 = m1.col1.y * m2.col1.x + m1.col2.y * m2.col1.y + m1.col3.y * m2.col1.z + m1.col4.y * m2.col1.w;
	float e3 = m1.col1.z * m2.col1.x + m1.col2.z * m2.col1.y + m1.col3.z * m2.col1.z + m1.col4.z * m2.col1.w;
	float e4 = m1.col1.w * m2.col1.x + m1.col2.w * m2.col1.y + m1.col3.w * m2.col1.z + m1.col4.w * m2.col1.w;

	float e5 = m1.col1.x * m2.col2.x + m1.col2.x * m2.col2.y + m1.col3.x * m2.col2.z + m1.col4.x * m2.col2.w;
	float e6 = m1.col1.y * m2.col2.x + m1.col2.y * m2.col2.y + m1.col3.y * m2.col2.z + m1.col4.y * m2.col2.w;
	float e7 = m1.col1.z * m2.col2.x + m1.col2.z * m2.col2.y + m1.col3.z * m2.col2.z + m1.col4.z * m2.col2.w;
	float e8 = m1.col1.w * m2.col2.x + m1.col2.w * m2.col2.y + m1.col3.w * m2.col2.z + m1.col4.w * m2.col2.w;

	float e9  = m1.col1.x * m2.col3.x + m1.col2.x * m2.col3.y + m1.col3.x * m2.col3.z + m1.col4.x * m2.col3.w;
	float e10 = m1.col1.y * m2.col3.x + m1.col2.y * m2.col3.y + m1.col3.y * m2.col3.z + m1.col4.y * m2.col3.w;
	float e11 = m1.col1.z * m2.col3.x + m1.col2.z * m2.col3.y + m1.col3.z * m2.col3.z + m1.col4.z * m2.col3.w;
	float e12 = m1.col1.w * m2.col3.x + m1.col2.w * m2.col3.y + m1.col3.w * m2.col3.z + m1.col4.w * m2.col3.w;

	float e13 = m1.col1.x * m2.col4.x + m1.col2.x * m2.col4.y + m1.col3.x * m2.col4.z + m1.col4.x * m2.col4.w;
	float e14 = m1.col1.y * m2.col4.x + m1.col2.y * m2.col4.y + m1.col3.y * m2.col4.z + m1.col4.y * m2.col4.w;
	float e15 = m1.col1.z * m2.col4.x + m1.col2.z * m2.col4.y + m1.col3.z * m2.col4.z + m1.col4.z * m2.col4.w;
	float e16 = m1.col1.w * m2.col4.x + m1.col2.w * m2.col4.y + m1.col3.w * m2.col4.z + m1.col4.w * m2.col4.w;

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
