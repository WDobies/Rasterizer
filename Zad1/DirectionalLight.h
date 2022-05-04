#pragma once
#include "Light.h"
#include "Matrix4.h"
#include <vector>
#include "Triangle.h"
#include "Mesh.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular, int shininess = 8, float specularStrenght = 0.5f);
	void Calculate(Mesh& mesh);
	Vector3 CalculatePhong(Triangle& triangle);
};

