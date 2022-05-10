#pragma once
#include "Light.h"
#include "Mesh.h"
class PointLightGourad : public Light
{
public:
	PointLightGourad(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess = 4, float specularStrenght = 0.9f);
	void Calculate(Mesh& mesh);
};

