#pragma once
#include "Light.h"
#include "Matrix4.h"
#include <vector>
#include "Triangle.h"
class DirectionalLight : public Light
{
public:
	void Calculate(Matrix4& camera, Matrix4& obj2view, int& vSize, std::vector<Vector3>& normals, std::vector<Vector3>& vertices , std::vector<Vector3>& color, std::vector<Vector3>& indices, std::vector<Triangle>& triangles);
};

