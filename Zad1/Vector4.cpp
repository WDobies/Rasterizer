#include "Vector4.h"


Vector4::Vector4(): x(0), y(0), z(0), w(0) {}

Vector4::Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

Vector4::Vector4(Vector3 vec3, float w)
{
	this->x = vec3.x;
	this->y = vec3.y;
	this->z = vec3.z;
	this->w = w;
}

Vector4 Vector4::One()
{
	return Vector4(1,1,1,1);
}

std::string Vector4::ToString() const
{
	std::string text = std::to_string(x) + " ";
	text += std::to_string(y) + " ";
	text += std::to_string(z) + " ";
	text += std::to_string(w) + "\n";
	return text;
}
