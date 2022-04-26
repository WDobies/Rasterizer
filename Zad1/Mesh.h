#pragma once
#include <vector>
#include "Vector3.h"
#include "Triangle.h"
class Mesh
{
public:
	int vSize;
	int tSize;

	std::vector<Vector3> vertices;
	std::vector<Vector3> indices;
	std::vector<Vector3> normals;
	std::vector<Vector3> colors;

	std::vector<Triangle> triangles;

	void CalculateNormals();
};

