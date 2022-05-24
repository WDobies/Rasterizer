#pragma once
#include "Light.h"
#include <vector>

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess = 16, float specularStrenght = 0.5f);
	Vector3 Calculate(Vector3 V, Vector3 N, Vector3 texture);
};

