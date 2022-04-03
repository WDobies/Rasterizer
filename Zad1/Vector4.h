#pragma once
#include "Vector3.hpp"
class Vector4
{
public:
	float x, y, z, w;

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 zyx, float w = 1);

	static Vector4 One();

	std::string ToString() const;

};

