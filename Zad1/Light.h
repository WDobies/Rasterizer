#pragma once
#include "Vector3.h"
class Light
{
public:
	Vector3 position;
	Vector3 ambientColor;
	Vector3 diffuseColor;
	Vector3 specularColor;

	int shininess;
	float specularStrenght;
};

