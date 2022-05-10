#pragma once
#include "Light.h"
#include "Matrix4.h"
#include <vector>
#include "Triangle.h"
#include "Mesh.h"
class DirectionalLightGourad : public Light
{
public:
	DirectionalLightGourad();
	DirectionalLightGourad(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess = 32, float specularStrenght = 0.3f);
	void Calculate(Mesh& mesh);
	Vector3 CalculatePhong(Triangle& triangle);
};

