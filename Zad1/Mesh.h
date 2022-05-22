#pragma once
#include <vector>
#include "Vector3.h"
#include "Triangle.h"
class Mesh
{
public:
	int vSize;
	int tSize;

	Matrix4 model;
	Matrix4 camera;
	Matrix4 projection;

	std::vector<Vector3> vertices;
	std::vector<Vector3> indices;
	std::vector<Vector3> normals;
	std::vector<Vector3> colors;
	std::vector<Vector3> texCoords;

	std::vector<Triangle> triangles;

	void CalculateNormals();
	void CalculateTexCoords();
	void SetCamera(Matrix4& camera);
	void SetProjection(Matrix4& projection);
	void SetModelMatrix(Matrix4& model);
	void SetView();
	void SetColor(const Vector3& color);
	void SetColorPerVertex(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	void Draw(int& i, int& j, ColorBuffer& buffer, Texture& texture);
};

