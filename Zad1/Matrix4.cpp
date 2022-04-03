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
	float row1 = (col1.x * b.x) + (col1.y * b.y) + (col1.z * b.z) + (col1.w * b.w);
	float row2 = col2.x * b.x + col2.y * b.y + col2.z * b.z + col2.w * b.w;
	float row3 = col3.x * b.x + col3.y * b.y + col3.z * b.z + col3.w * b.w;
	float row4 = col4.x * b.x + col4.y * b.y + col4.z * b.z + col4.w * b.w;
	std::cout <<"Perspe"<< row1 << " " << row2 << " " << row3 << " " << row4 << "\n";
	return Vector4(row1,row2,row3,row4);
}

Matrix4& Matrix4::Perspective(float fov, float aspect, float near, float far)
{
	fov *= 3.14 / 360.f;
	float f = cos(fov) / sin(fov);
	col1 = Vector4(f / aspect, 0, 0, 0);
	col2 = Vector4(0, f, 0, 0);
	col3 = Vector4(0, 0, (far + near) / (near - far), -1);
	col4 = Vector4(0, 0, (2*far*near) / (near - far), 0);
	return *this;
}

std::string Matrix4::ToString() const
{
	std::string text = col1.ToString();
	text += col2.ToString();
	text += col3.ToString();
	text += col4.ToString(); + "\n";
	return text;
}
