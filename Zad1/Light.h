#pragma once
#include "Vector3.h"
class Light
{
public:
	Vector3 position;
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;

	Light();
	void Calculate();
};

